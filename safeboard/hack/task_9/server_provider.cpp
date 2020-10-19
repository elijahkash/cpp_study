#include "server_provider.hpp"

#include <chrono>

namespace remote {

ServerProvider::ServerProvider(const ServerProviderSettings *settings)
  : settings(*settings)
  , optimal(std::nullopt)
  , exit(false)
  , fail(false)
  , changeSettings(true) {
  try {
    worker = std::thread(&ServerProvider::workerThread, this);
  }
  catch (...) {
    fail.store(true);
  }
}

ServerProvider::~ServerProvider() {
  exit.store(true);
  if (worker.joinable())
    try {
      worker.join();
    }
    catch (...) {
    }
}

ResultCode ServerProvider::GetRemoteServiceAddress(std::string& address) {
  if (fail.load())
    return Fail;
  try {
    std::lock_guard<std::mutex> lock(accessMutex);
    if (optimal.has_value()) {
      address = *optimal;
      return Ok;
    }
    return Undefined;
  }
  catch (...) {
    // fail.store(true);
    return Fail;
  }
}

uint32_t ServerProvider::SetSettings(const ServerProviderSettings *newSettings) {
  if (fail.load())
    return Fail;
  try {
    std::lock_guard<std::mutex> lock(accessMutex);
    settings = *newSettings;
    changeSettings.store(true);
    optimal.reset();
  }
  catch (...) {
    fail.store(true);
    return Fail;
  }
  return Ok;
}

uint32_t ServerProvider::GetSettings(ServerProviderSettings *dstSettings) {
  if (fail.load())
    return Fail;
  try {
    std::lock_guard<std::mutex> lock(accessMutex);
    *dstSettings = settings;
  }
  catch (...) {
    // fail.store(true);
    return Fail;
  }
  return Ok;
}

ResultCode ServerProvider::status() const {
  if (fail.load())
    return Fail;
  if (optimal.has_value())
    return Ok;
  return Undefined;
}

ResultCode ServerProvider::workerThread() {
  try {  // case std::chrono exceptions
    std::chrono::time_point last(std::chrono::system_clock::now());
    while (not exit.load() and not fail.load()) {
      std::chrono::time_point cur(std::chrono::system_clock::now());
      if (not changeSettings.load() and cur - last < updateTime) {
        std::this_thread::sleep_for(checkTime);
        continue;
      }
      last = cur;
      chooseOptimal();
    }
  }
  catch (...) {
    fail.store(true);
    return Fail;
  }
  return Ok;
}

void ServerProvider::chooseOptimal() {
  std::unique_lock<std::mutex> lck(accessMutex);
  ServerProviderSettings curSettings(settings);
  changeSettings.store(false);
  std::optional<std::string> oldOptimal(optimal);
  lck.unlock();

  std::optional<std::string> newOptimal;
  try {
    // potential very expensive methods
    if (curSettings.searchMode == Local)
      newOptimal = searchLocal(
          oldOptimal, curSettings.localSearchSettings, curSettings.servers);
    else
      newOptimal = searchSmart(
          oldOptimal, curSettings.smartSearchSettings, curSettings.servers);

  }
  catch (...) {
    newOptimal = std::nullopt;
  }

  lck.lock();
  if (not changeSettings.load())
    optimal = std::move(newOptimal);
  // for repeat try immediately
  if (not optimal.has_value())
    changeSettings.store(true);
  lck.unlock();
}

std::optional<std::string> ServerProvider::searchLocal(
    std::optional<std::string>& old,
    LocalSearchSettings& locSetting,
    std::vector<RemoteService> services) {
  RemoteService* minCity = nullptr;
  RemoteService* minGeneral = nullptr;
  RemoteService* oldService = nullptr;
  for (auto& service : services) {
    if (service.areaLevel == City
        and (not minCity or service.clients < minCity->clients))
      minCity = &service;
    if (not minCity
        and (not minGeneral or service.clients < minGeneral->clients))
      minGeneral = &service;
    if (not oldService and old.has_value() and service.address == *old)
      oldService = &service;
  }
  RemoteService* newOptimal = minCity ? minCity : minGeneral;
  if (oldService and (not newOptimal or
                      ((long long)oldService->clients) - newOptimal->clients <
                      locSetting.diffInClients))
    return old;
  return (newOptimal ? std::optional<std::string>(newOptimal->address)
                       : std::nullopt);
}

bool match_tags(std::string& dstTag, std::string serviceTags) {
  std::string delimiter = "#";
  size_t pos = 0;
  std::string token;
  while ((pos = serviceTags.find(delimiter)) != std::string::npos) {
    token = serviceTags.substr(0, pos);
    if (token == dstTag)
      return true;
    serviceTags.erase(0, pos + delimiter.length());
  }
  return false;
}

std::optional<std::string> ServerProvider::searchSmart(
    std::optional<std::string>& old,
    SmartSearchSettings& smartSetting,
    std::vector<RemoteService> services) {
  RemoteService* newOptimal = nullptr;
  RemoteService* oldService = nullptr;
  uint64_t total = 0;
  for (auto& service : services) {
    if ((service.areaLevel <= smartSetting.areaLevelRestriction
        or match_tags(service.tag, smartSetting.tags))
        and (not newOptimal or service.clients < newOptimal->clients)) {
      newOptimal = &service;
      total += service.clients;
    }
    if (not oldService and old.has_value() and service.address == *old)
      oldService = &service;
  }
  if (oldService and (not newOptimal or
      (((float)oldService->clients) - newOptimal->clients) * 100 / total <
          smartSetting.diffInClientsPercents))
    return old;
  return (newOptimal ? std::optional<std::string>(newOptimal->address)
                     : std::nullopt);
}

}
