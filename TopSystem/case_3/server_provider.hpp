#ifndef CASE_3_SERVER_PROVIDER_HPP_
#define CASE_3_SERVER_PROVIDER_HPP_

#include <thread>
#include <mutex>
#include <atomic>
#include <optional>

#include "contracts.hpp"

namespace remote {

class ServerProvider : public IServerProvider, public IServerProviderSettings {
 public:
  explicit ServerProvider(const ServerProviderSettings* settings);
  ~ServerProvider();

  ResultCode GetRemoteServiceAddress(std::string& address) override;
  uint32_t SetSettings(const ServerProviderSettings* settings) override;
  uint32_t GetSettings(ServerProviderSettings* settings) override;

  ResultCode status();

 private:
  // TODO: set a suitable time or implement as configurable variables!
  constexpr static std::chrono::milliseconds chooseOptimalTime{50};
  constexpr static std::chrono::milliseconds checkTime{50};
  constexpr static std::chrono::seconds updateTime{30};

  std::thread worker;
  std::mutex accessMutex;

  ServerProviderSettings settings;
  std::optional<std::string> optimal;

  std::atomic<bool> exit;
  std::atomic<bool> fail;
  std::atomic<bool> changeSettings;

  ResultCode workerThread();
  void chooseOptimal();

  // TODO: this is fast non-extensible solution
  static std::optional<std::string> searchLocal(
      std::optional<std::string>& old,
      LocalSearchSettings& locSetting,
      std::vector<RemoteService> services);
  static std::optional<std::string> searchSmart(
      std::optional<std::string>& old,
      SmartSearchSettings& smartSetting,
      std::vector<RemoteService> services);
};

}

#endif  // CASE_3_SERVER_PROVIDER_HPP_
