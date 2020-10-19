#include <iostream>
#include <exception>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>

#include "wrap_error.hpp"


// This is dirty hack. But a have some real problems in general (I'm work from
// School21 iMac, and for a reason of technical issues a start solved tasks
// after an hour (14:15). So just real hurry!
std::string err;

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
  Drop, Apply, Validate, Error
};

struct Request
{
  RequestType type;
  uint64_t ownerId;
};

RequestType GetRequestType(const RequestFromConfig& request) noexcept
{
  if (request.type == "drop")
    return RequestType::Drop;
  if (request.type == "apply")
    return RequestType::Apply;
  if (request.type == "validate")
    return RequestType::Validate;
  err = string("unknown type '") + request.type + "'";
  return RequestType::Error;
}

Request BuildRequest(const vector<Requester>& availableRequesters, const RequestFromConfig& requestFromConfig) noexcept
{

  Request request;
  auto it = find_if(begin(availableRequesters), end(availableRequesters), [&](const Requester& requester)
  {return requester.name == requestFromConfig.requester; });
  if (it == end(availableRequesters)) {
    request.ownerId = 0;
    request.type = RequestType::Error;
    err = string("unknown requester '") + requestFromConfig.requester + "'";
    return request;
  }
  request.type = GetRequestType(requestFromConfig);
  request.ownerId = it->ownerId;
  return request;

}

struct Queue
{
  uint32_t id;
  vector<Request> requests;
};

Queue BuildRequestQueue(const vector<Requester>& availableRequesters, const vector<RequestFromConfig>& requests) noexcept
{
  static uint32_t nextId = 0;
  nextId++;

  Queue result;
  result.id = nextId;
  for (const auto& requestFromConfig : requests) {
    auto res = BuildRequest(availableRequesters, requestFromConfig);
    if (not res.ownerId or res.type == RequestType::Error) {
      ostringstream message("");
      message << "can't build request queue #" << nextId << '\n' << " because: ";
      err = message.str() + err;
      result.id = 0;
      return result;
    }
    result.requests.push_back(res);
  }
  return result;

}

// void print_exception(const std::exception& e, int level = 0) noexcept
void print_exception() noexcept
{
  std::cout << "high-level operation failed: " << err;
}


void PrintTaskResult(const vector<Requester>& availableRequesters, const vector<RequestFromConfig>& requests) noexcept
{
  err = "";
  auto queue = BuildRequestQueue(availableRequesters, requests);
  if (not queue.id) {
    print_exception();
    cout << endl << endl;
    return;
  }
  for (const auto& request : queue.requests)
    cout << "request in queue #" << queue.id << ": " << static_cast<int>(request.type) << " / " << request.ownerId << endl;
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
