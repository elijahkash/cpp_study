#include <iostream>

#include "server_provider.hpp"

using namespace remote;

int main() {
  ServerProviderSettings settings;
  std::vector<RemoteService> servers;
  servers.emplace_back(3000, City, "", "10.70.140.80");
  servers.emplace_back(0, Country, "", "10.70.140.81");
  settings.servers = servers;

  ServerProvider serverProvider(&settings);

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  std::string res;
  ResultCode code;
  code = serverProvider.GetRemoteServiceAddress(res);
  std::cout << code << ' ' << res << std::endl;

  settings.servers.emplace_back(2995, City, "", "10.70.140.82");
  code = serverProvider.GetRemoteServiceAddress(res);
  std::cout << code << ' ' << res << std::endl;

  settings.localSearchSettings.diffInClients = 2;
  serverProvider.SetSettings(&settings);

  std::this_thread::sleep_for(std::chrono::milliseconds(100));


  code = serverProvider.GetRemoteServiceAddress(res);
  std::cout << code << ' ' << res << std::endl;
  return 0;
}

