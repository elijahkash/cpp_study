#ifndef CASE_1_EXAMPLE_HPP_
#define CASE_1_EXAMPLE_HPP_

#include <vector>
#include <map>
#include <string>

struct Requester {
  std::string name;
  uint64_t ownerId;
};

struct RequestFromConfig {
  std::string name;
  std::string requester;
  std::string type;
};

enum class RequestType {
  Drop, Apply, Validate
};

struct Request {
  RequestType type;
  uint64_t ownerId;
};

void PrintTaskResult(const std::vector<Requester>& availableRequesters,
                     const std::vector<RequestFromConfig>& requests) noexcept;

#endif  // CASE_1_EXAMPLE_HPP_
