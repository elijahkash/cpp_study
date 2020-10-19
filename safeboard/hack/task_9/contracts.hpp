#ifndef SAFEBOARD_HACK_TASK_9_CONTRACTS_HPP_
#define SAFEBOARD_HACK_TASK_9_CONTRACTS_HPP_

#include <cstdint>
#include <string>
#include <vector>

namespace remote {

enum ResultCode {
  Ok = 0,
  Fail,
  Undefined
};

struct IServerProvider {
  // address (out):
  //   Address of current scan server (chosen by last iteration of algorithm call)
  // return:
  //   Ok on success
  //   Fail in case of any errors
  //   Undefined in case of current scan server is undefined (there was no optimal server by last last iteration of algorithm call)
  virtual ResultCode GetRemoteServiceAddress(std::string& address) = 0;
};

const uint32_t DiffInClientsDefaultForLocal = 50;

struct LocalSearchSettings {
  uint32_t diffInClients;

  LocalSearchSettings()
      : diffInClients(DiffInClientsDefaultForLocal) {}
};

enum AreaLevel {
  City = 0,
  Country,
  Area,
  None
};

const uint32_t DiffInClientsDefaultForSmartPercents = 20;

struct SmartSearchSettings {
  uint32_t diffInClientsPercents;

  // Set of tags with delimiter equal to #
  // Example: "tag0#tag1#tag2"
  std::string tags;

  AreaLevel areaLevelRestriction;

  SmartSearchSettings()
      : diffInClientsPercents(DiffInClientsDefaultForSmartPercents)
      , areaLevelRestriction(None) {}
};

// Information about one of scan servers, one of an item in "std::vector<RemoteService> servers" collection,
// passed by an admin to ServerProvider via IServerProviderSettings
struct RemoteService {
  uint32_t clients;

  AreaLevel areaLevel;

  std::string tag;

  std::string address;

  RemoteService()
      : clients(0)
      , areaLevel(None) {}

  RemoteService(uint32_t clients, AreaLevel area_level,
                std::string tag, std::string address)
      : clients(clients)
      , areaLevel(area_level)
      , tag(tag)
      , address(address) {}
};

enum SearchMode {
  Local = 0,
  Smart
};

struct ServerProviderSettings {
  // Scan server addresses collection to choose optimal from.
  // Initially empty, sets by an admin.
  std::vector<RemoteService> servers;

  // One of two algorithm to use for choose of scan server
  SearchMode searchMode;

  LocalSearchSettings localSearchSettings;
  SmartSearchSettings smartSearchSettings;

  ServerProviderSettings()
      : searchMode(Local) {}
};

struct IServerProviderSettings {
  // settings (in)
  // return:
  //   Ok on success
  //   Fail in case of any errors
  virtual uint32_t SetSettings(const ServerProviderSettings* settings) = 0;
  // settings (out)
  // return:
  //   Ok on success
  //   Fail in case of any errors
  virtual uint32_t GetSettings(ServerProviderSettings* settings) = 0;
};

}  // namespace remote

#endif  // SAFEBOARD_HACK_TASK_9_CONTRACTS_HPP_
