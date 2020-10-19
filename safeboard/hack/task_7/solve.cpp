#include <iostream>
#include <exception>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>

#include "wrap_error.hpp"

using namespace std;
struct Requester
{
  string name;
  uint64_t ownerId;
};

struct RequestFromConfig
{
  string name;
  string requester;
  string type;
};

enum class RequestType
{
  Drop, Apply, Validate
};

struct Request
{
  RequestType type;
  uint64_t ownerId;
};

WrapError<RequestType> GetRequestType(const RequestFromConfig& request) noexcept
{
  if (request.type == "drop")
    return WrapError<RequestType>(RequestType::Drop);
    // if doesn't mark WrapError(T& val) as explicit:
    // return RequestType::Drop;
  if (request.type == "apply")
    return WrapError<RequestType>(RequestType::Apply);
  if (request.type == "validate")
    return WrapError<RequestType>(RequestType::Validate);
  return WrapError<RequestType>(string("unknown type '") + request.type + "'");
  // throw runtime_error(string("unknown type '") + request.type + "'");
}

WrapError<Request> BuildRequest(const vector<Requester>& availableRequesters, const RequestFromConfig& requestFromConfig) noexcept
{
  Request request;
  auto it = find_if(begin(availableRequesters), end(availableRequesters), [&](const Requester& requester)
  {return requester.name == requestFromConfig.requester; });
  if (it == end(availableRequesters))
    return WrapError<Request>(string("unknown requester '") + requestFromConfig.requester + "'");
    // throw runtime_error(string("unknown requester '") + requestFromConfig.requester + "'");
  auto tmp = GetRequestType(requestFromConfig);
  if (tmp.hasError())
    return WrapError<Request>(std::move(tmp.getErrors()));
  request.type = tmp();
  request.ownerId = it->ownerId;
  return WrapError<Request>(request);

}

struct Queue
{
  uint32_t id;
  vector<Request> requests;
};

WrapError<Queue> BuildRequestQueue(const vector<Requester>& availableRequesters, const vector<RequestFromConfig>& requests) noexcept
{
  static uint32_t nextId = 0;
  nextId++;
  // try
  // {
  Queue result;
  result.id = nextId;
  for (const auto& requestFromConfig : requests) {
    auto tmp = BuildRequest(availableRequesters, requestFromConfig);
    if (tmp.hasError()) {
      ostringstream message("");
      message << "can't build request queue #" << nextId;
      return WrapError<Queue>(message.str(), std::move(tmp.getErrors()));
    }
    result.requests.push_back(tmp());
  }
  return WrapError<Queue>(result);
  // }

  // catch (...)
  // {
  //   ostringstream message("");
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
    cout << string(i, ' ')
         << (i ? "because: " : "high-level operation failed: ")
         << error
         << '\n';
    i++;
  }
}


void PrintTaskResult(const vector<Requester>& availableRequesters, const vector<RequestFromConfig>& requests) noexcept
{
  // try
  // {
  auto queue = BuildRequestQueue(availableRequesters, requests);
  if (queue.hasError())
    print_exception(std::move(queue.getErrors()));
  else
    for (const auto& request : queue().requests)
      cout << "request in queue #" << queue().id << ": " << static_cast<int>(request.type) << " / " << request.ownerId << endl;
  // }
  // catch (const std::exception& ex)
  // {
  //   print_exception(ex);
  // }
  cout << endl << endl;
}

///////////////////////////////////////////////////////////////////////////////

int main() // examples
{
  PrintTaskResult(
      { { "first_requester", 1 }, { "second_requester", 2 }, { "third_requester", 3 } },
      { { "Johny", "second_requester", "drop" }, { "Sam", "second_requester", "apply" }, { "Louise", "first_requester", "apply" } });
  /* [output]

  request in queue #1: 0 / 2
  request in queue #1: 1 / 2
  request in queue #1: 1 / 1

  */
  PrintTaskResult(
      { { "second_requester", 2 }, { "third_requester", 3 } },
      { { "Johny", "second_requester", "drop" }, { "Sam", "second_requester", "apply" }, { "Louise", "first_requester", "apply" } });
  /* [output]

  high-level operation failed: can't build request queue #2
   because: unknown requester 'first_requester'
  */

  PrintTaskResult(
      { { "first_requester", 1 }, { "second_requester", 2 }, { "third_requester", 3 } },
      { { "Johny", "third_requester", "drop" }, { "Sam", "third_requester", "apply" }, { "Louise", "first_requester", "apply" } });

  /* [output]
  request in queue #3: 0 / 3
  request in queue #3: 1 / 3
  request in queue #3: 1 / 1
  */

  PrintTaskResult(
      { { "first_requester", 1 }, { "second_requester", 2 }, { "third_requester", 3 } },
      { { "Johny", "second_requester", "drop" }, { "Sam", "second_requester", "apply" }, { "Louise", "first_requester", "reapply" } });
  /* [output]
  high-level operation failed: can't build request queue #4
   because: unknown type 'reapply'
  */
  return 0;
}
