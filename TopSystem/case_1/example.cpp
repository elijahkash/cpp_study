#include "example.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
// #include <exception>

#include "wrap_error.hpp"

WrapError<RequestType> GetRequestType(
    const RequestFromConfig& request) noexcept {
  if (request.type == "drop")
    return WrapError<RequestType>(RequestType::Drop);
    // if doesn't mark WrapError(T& val) as explicit:
    // return RequestType::Drop;
  if (request.type == "apply")
    return WrapError<RequestType>(RequestType::Apply);
  if (request.type == "validate")
    return WrapError<RequestType>(RequestType::Validate);
  return WrapError<RequestType>(std::string("unknown type '")
                                + request.type + "'");
  // throw runtime_error(std::string("unknown type '") + request.type + "'");
}

WrapError<Request> BuildRequest(
    const std::vector<Requester>& availableRequesters,
    const RequestFromConfig& requestFromConfig) noexcept {
  Request request;
  auto it = find_if(begin(availableRequesters),
                    end(availableRequesters),
                    [&](const Requester& requester)
                    { return requester.name == requestFromConfig.requester; });
  if (it == end(availableRequesters))
    return WrapError<Request>(std::string("unknown requester '")
                              + requestFromConfig.requester + "'");
    // throw runtime_error(std::string("unknown requester '")
    //                     + requestFromConfig.requester + "'");
  auto tmp = GetRequestType(requestFromConfig);
  if (tmp.hasError())
    return WrapError<Request>(std::move(tmp.getErrors()));
  request.type = tmp();
  request.ownerId = it->ownerId;
  return WrapError<Request>(request);

}

struct Queue {
  uint32_t id;
  std::vector<Request> requests;
};

WrapError<Queue> BuildRequestQueue(
    const std::vector<Requester>& availableRequesters,
    const std::vector<RequestFromConfig>& requests) noexcept {
  static uint32_t nextId = 0;
  nextId++;
  // try
  // {
  Queue result;
  result.id = nextId;
  for (const auto& requestFromConfig : requests) {
    auto tmp = BuildRequest(availableRequesters, requestFromConfig);
    if (tmp.hasError()) {
      std::ostringstream message("");
      message << "can't build request queue #" << nextId;
      return WrapError<Queue>(message.str(), std::move(tmp.getErrors()));
    }
    result.requests.push_back(tmp());
  }
  return WrapError<Queue>(result);
  // }
  // catch (...)
  // {
  //   std::ostringstream message("");
  //   message << "can't build request queue #" << nextId;
  //   std::throw_with_nested(std::runtime_error(message.str()));
  // }
}

// void print_exception(const std::exception& e, int level = 0)
// {
//   cout << string(level, ' ') << (level ? "because: " : "high-level operation failed: ") << e.what() << '\n';
//   try
//   {
//     std::rethrow_if_nested(e);
//   }
//   catch (const std::exception& e)
//   {
//     print_exception(e, level + 1);
//   }
//   catch (...) {}
// }

void print_exception(std::list<std::string>&& errors) noexcept {
  int i = 0;
  for (const auto& error : errors) {
    std::cout << std::string(i, ' ')
         << (i ? "because: " : "high-level operation failed: ")
         << error
         << '\n';
    i++;
  }
}


void PrintTaskResult(
    const std::vector<Requester>& availableRequesters,
    const std::vector<RequestFromConfig>& requests) noexcept {
  // try
  // {
  auto queue = BuildRequestQueue(availableRequesters, requests);
  if (queue.hasError())
    print_exception(std::move(queue.getErrors()));
  else
    for (const auto& request : queue().requests)
      std::cout << "request in queue #" << queue().id << ": "
                << static_cast<int>(request.type) << " / " << request.ownerId
                << std::endl;
  // }
  // catch (const std::exception& ex)
  // {
  //   print_exception(ex);
  // }
  // std::cout << std::endl << std::endl;
}
