#include <iostream>
#include <random>
#include <functional>

#include "server_provider.hpp"

// tested on:
//  - g++ (Ubuntu 10.2.0-5ubuntu1~20.04) 10.2.0
//  - clang version 10.0.0-4ubuntu1
// C++17

using namespace remote;

const int numberOfAdmins = 2;
const int numberOfClients = 20;

// time for test in seconds
const int testTime = 10;
// in milliseconds
const int adminBottomTimeBound = 400;
const int adminUpperTimeBound = 1000;
const int clientBottomTimeBound = 0;
const int clientUpperTimeBound = 5;

const int clientsOnServerBottom = 0;
const int clientsOnServerUpper = 1000;

std::random_device dev;
std::default_random_engine randEngine(dev());
std::uniform_int_distribution<int> distributionAdmin(adminBottomTimeBound,
                                                     adminUpperTimeBound);
std::uniform_int_distribution<int> distributionClient(clientBottomTimeBound,
                                                      clientUpperTimeBound);
std::uniform_int_distribution<int> distributionServerClients(
    clientsOnServerBottom, clientsOnServerUpper);

auto adminTime = [](){
  return std::chrono::milliseconds(distributionAdmin(randEngine));
};
auto clientTime = [](){
  return std::chrono::milliseconds(distributionServerClients(randEngine));
};
auto clientsOnServer = [](){
  return distributionServerClients(randEngine);
};

void printServers(const std::vector<RemoteService>& servers) {
  std::cout << "Configuration:\n";
  for (const auto& item : servers) {
    std::cout << item.clients << '\t' << item.areaLevel << '\t'
              << item.address << '\t' << item.tag << std::endl;
  }
}

void requester(ServerProvider* service,
               std::chrono::time_point<std::chrono::system_clock> endTime) {
  std::string res;
  ResultCode code;
  while (std::chrono::system_clock::now() < endTime) {
    std::this_thread::sleep_for(clientTime());
    code = service->GetRemoteServiceAddress(res);
    std::cout << code << ' ' << res << std::endl;
  }
}

void admin(ServerProvider* service,
           std::chrono::time_point<std::chrono::system_clock> endTime) {
  while (std::chrono::system_clock::now() < endTime) {
    std::this_thread::sleep_for(adminTime());
    ServerProviderSettings tmp;
    service->GetSettings(&tmp);

    for (auto& servers: tmp.servers)
      servers.clients = clientsOnServer();
    printServers(tmp.servers);

    service->SetSettings(&tmp);
  }
}

int main() {
  ServerProviderSettings settings;
  std::vector<RemoteService> servers;
  servers.emplace_back(0, City,     "tag1",       "10.70.140.80");
  servers.emplace_back(0, Country,  "tag1#tag2",  "10.70.140.81");
  servers.emplace_back(0, City,     "tag2#tag3",  "10.70.140.82");
  servers.emplace_back(0, Country,  "tag3#",      "10.70.140.83");
  servers.emplace_back(0, City,     "tag1#tag4",  "10.70.140.84");
  servers.emplace_back(0, City,     "tag2",       "10.70.140.85");
  servers.emplace_back(0, Area,     "tag3#tag4",  "10.70.140.86");
  settings.servers = servers;

  printServers(servers);

  ServerProvider serverProvider(&settings);

  auto start = std::chrono::system_clock::now();
  auto finish = start + std::chrono::seconds(testTime);

  std::vector<std::thread> threads;
  for (int i = 0; i < numberOfAdmins; i++)
    threads.emplace_back(std::thread(admin, &serverProvider, finish));
  for (int i = 0; i < numberOfClients; i++)
    threads.emplace_back(std::thread(requester, &serverProvider, finish));

  for (auto& thread : threads)
    thread.join();

  return 0;
}

