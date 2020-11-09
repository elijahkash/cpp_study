#include "example.hpp"

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