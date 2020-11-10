#include <ostream>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "example.hpp"

// this is for catch output from std::cout
std::ostringstream catchOutput(
    const std::vector<Requester> &availableRequesters,
    const std::vector<RequestFromConfig> &requests) {
  std::streambuf* defaultCOUT = std::cout.rdbuf();
  std::ostringstream customCOUT;
  std::cout.rdbuf(customCOUT.rdbuf());
  PrintTaskResult(availableRequesters, requests);
  std::cout.rdbuf(defaultCOUT);
  return std::move(customCOUT);
}

TEST_CASE("test_1") {
  std::vector<Requester> availableRequesters = {
      { "first_requester", 1 },
      { "second_requester", 2 },
      { "third_requester", 3 }
  };
  std::vector<RequestFromConfig> requests {
      { "Johny", "second_requester", "drop" },
      { "Sam", "second_requester", "apply" },
      { "Louise", "first_requester", "apply" }
  };

  std::string result = "request in queue #1: 0 / 2\n"
                       "request in queue #1: 1 / 2\n"
                       "request in queue #1: 1 / 1\n";

  REQUIRE(catchOutput(availableRequesters, requests).str() == result);
}

TEST_CASE("test_2") {
  std::vector<Requester> availableRequesters = {
      { "second_requester", 2 },
      { "third_requester", 3 }
  };
  std::vector<RequestFromConfig> requests {
      { "Johny", "second_requester", "drop" },
      { "Sam", "second_requester", "apply" },
      { "Louise", "first_requester", "apply" }
  };

  std::string result = "high-level operation failed: can't build request queue #2\n"
                       " because: unknown requester 'first_requester'\n";

  REQUIRE(catchOutput(availableRequesters, requests).str() == result);
}

TEST_CASE("test_3") {
  std::vector<Requester> availableRequesters = {
      { "first_requester", 1 },
      { "second_requester", 2 },
      { "third_requester", 3 }
  };
  std::vector<RequestFromConfig> requests {
      { "Johny", "third_requester", "drop" },
      { "Sam", "third_requester", "apply" },
      { "Louise", "first_requester", "apply" }
  };

  std::string result = "request in queue #3: 0 / 3\n"
                       "request in queue #3: 1 / 3\n"
                       "request in queue #3: 1 / 1\n";

  REQUIRE(catchOutput(availableRequesters, requests).str() == result);
}

TEST_CASE("test_4") {
  std::vector<Requester> availableRequesters = {
      { "first_requester", 1 },
      { "second_requester", 2 },
      { "third_requester", 3 }
  };
  std::vector<RequestFromConfig> requests {
      { "Johny", "second_requester", "drop" },
      { "Sam", "second_requester", "apply" },
      { "Louise", "first_requester", "reapply" }
  };

  std::string result = "high-level operation failed: can't build request queue #4\n"
                       " because: unknown type 'reapply'\n";

  REQUIRE(catchOutput(availableRequesters, requests).str() == result);
}
