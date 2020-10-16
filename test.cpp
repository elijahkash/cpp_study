#include <iostream>
#include <vector>
#include <algorithm>

#include <optional>

class Info {
 public:
  Info(int weight, int back_row, int back_col)
  : weight(weight), back_row(back_row), back_col(back_col) {}

  int weight;
  int back_row;
  int back_col;
};

class Way {
 public:
  Way(int row, int col, int len): row(row), col(col), len(len) {}

  int row;
  int col;
  int len;
};

inline bool operator< (const Way& lhs, const Way& rhs){
  return (lhs.len > rhs.len);
}

std::vector<std::pair<int, int>> getMoves(
    const std::vector<std::vector<int>>& map, Way pos) {
  std::vector<std::pair<int, int>> res;
  std::pair<int, int> vec;
  int row = pos.row;
  int col = pos.col;
  switch (map[row][col]) {
    case 1:
      vec.first = -1;
      vec.second = -1;
      break;
    case 2:
      vec.first = -1;
      vec.second = 0;
      break;
    case 3:
      vec.first = -1;
      vec.second = 1;
      break;
    case 4:
      vec.first = 0;
      vec.second = -1;
      break;
    case 6:
      vec.first = 0;
      vec.second = 1;
      break;
    case 7:
      vec.first = 1;
      vec.second = -1;
      break;
    case 8:
      vec.first = 1;
      vec.second = 0;
      break;
    case 9:
      vec.first = 1;
      vec.second = 1;
      break;
  }
  while ((row + vec.first) >= 0 and (row + vec.first) < map.size()
         and (col + vec.second) >= 0 and (col + vec.second) < map[0].size()) {
    row += vec.first;
    col += vec.second;
    res.emplace_back(row, col);
  }
}

std::optional<std::pair<int, int>> inserts(
    const std::vector<std::vector<int>>& map,
    std::vector<std::vector<Info>>* weights,
    std::vector<Way>* ways) {
  Way cur = ways->back();
  ways->pop_back();
  auto moves = getMoves(map, cur);
  std::optional<std::pair<int, int>> res(std::nullopt);
  for (auto& item: moves) {
    if ((*weights)[item.first][item.second].weight == -1) {
      (*weights)[item.first][item.second].back_row = cur.row;
      (*weights)[item.first][item.second].back_col = cur.col;
      (*weights)[item.first][item.second].weight = cur.len + 1;
    }
    if (map[item.first][item.second] == 5) {
      res = {item.first, item.second};
    }
    (*ways).emplace_back(cur.len + 1, item.first, item.second);
  }

  std::sort(ways->begin(), ways->end());
}

void restore_and_print(std::pair<int, int> end,
                       std::vector<std::vector<Info>>& weights) {
  std::vector<std::pair<int, int>> res;
  Info cur = weights[end.first][end.second];
  // int cur = weights[end.first][end.second].weight;
  res.emplace_back(end.first, end.second);
  while (true) {
   Info tmp = weights[cur.back_row][cur.back_col];
   if (tmp.weight == 0) {
     for (int i = res.size(); i > 0; i--) {
       std::cout << '(' << res[i-1].first << ',' << res[i-1].second << ");";
     }
     return ;
   }
   res.emplace_back(cur.back_row, cur.back_col);
   cur = tmp;
  }
}

int main() {
  char ch;
  std::cin >> ch;
  int size = ch - '0';

  std::cin >> ch;
  int start_row = ch - '0';
  std::cin >> ch;
  int start_col = ch - '0';

  std::vector<std::vector<int>> map;
  for (int i = 0; i < size; i++) {
    map.emplace_back();
    for (int j = 0; j < size; j++) {
      std::cin >> ch;
      int val = ch - '0';
      map.emplace_back(val);
    }
  }

  if (map[start_row][start_col] == 5)
    return 0;

  std::vector<std::vector<Info>> weights;
  for (auto& row : weights)
    for (auto& col : row)
      col = Info(-1, -1, -1);
  weights[start_row][start_col] = Info(0, start_row, start_col);

  std::vector<Way> ways;
  ways.emplace_back(start_row, start_col, 0);

  while (not ways.empty()) {
    auto tmp = inserts(map, &weights, &ways);
    if (tmp.has_value()) {
      restore_and_print(*tmp, weights);
      return 0;
    }
  }

  return 0;
}



/*#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <exception>

// logs - pointer, not reference (for changing.
// according with C++ Core GuidLines)
bool deletes(std::vector<std::vector<int>>* logs, int time) {
  for (auto& item : *logs) {
    while (not item.empty() and item[1] <= time) {
      // delete [0] and [1]
      // need to use lists? or reverse vector after input...
      item.erase(item.begin(), item.begin() + 2);
      if (item.empty())
        return false;
    }
  }
  return true;
}

// wait even number for every log!
std::vector<std::pair<int, int>>
calc(std::vector<std::vector<int>> logs) {
  std::vector<std::pair<int, int>> res;
  // TODO: place deletes() in loop condition?
  while (true) {
    int max_start = logs[0][0];
    int min_end = logs[0][1];

    // TODO: not check first!
    for (auto& item : logs) {
      max_start = std::max(max_start, item[0]);
      min_end = std::min(min_end, item[1]);
    }
    if (max_start < min_end) {
      res.emplace_back(max_start, min_end);
      // max_start = min_end;
    }
    if (not deletes(&logs, min_end))
      return res;
  }
}

int main(int argc, char *argv[]) {
  // Work not only with 3 logs! use this var for change logs count:
  const int LOGS_COUNT = 3;
  std::vector<std::vector<int>> logs;

  if (argc != LOGS_COUNT + 1) {
    std::cout << "Error: wrong count of logs!" << std::endl;
    return 0;
  }

  for (int i = 0; i < LOGS_COUNT; i++) {
    std::fstream file(argv[i + 1]);
    if (!file.is_open()) {
      std::cout << "Error: failed to open " << argv[i + 1] << std::endl;
      return 0;
    }
    logs.emplace_back();
    int nbr;
    while (file >> nbr)
      logs[i].push_back(nbr);

    // TODO: common policy with general result?
    if (logs[i].empty()) {
      std::cout << "OK" << std::endl;
      return 0;
    }

    if (logs[i].size() % 2)
      throw std::runtime_error("Sorry, logs with not closed "
                               "interval not implemented!");
    file.close();
  }

  // copy vector (for change inside)
  auto res = calc(logs);

  if (res.empty())
    std::cout << "OK" << std::endl;
  else
    for (auto& item : res)
      std::cout << item.first << ' ' << item.second << std::endl;

  return 0;
}*/

// TODO: this??? task 5
/*#include <vector>
#include <iostream>
#include <algorithm>

int mDiff = 0;

int func(const std::vector<std::vector<int>>& a, int row, int col) {
  if (row == a.size() - 1)
    return a[row][col];
  int i = col - mDiff;
  int j = col + mDiff + 1;
  if (i < 0)
    i = 0;
  if (i >= a[row + 1].size())
    return -1;
  if (j >= a[row + 1].size())
    j = a[row + 1].size();

  std::vector<int> vals;
  for (int iter = i; iter < j; iter++)
    vals.push_back(func(a, row + 1, iter));


  if (vals.empty())
    return -1;
  int min = *std::max_element(vals.begin(), vals.end());
  for (auto& item : vals)
    if (item != -1 and item < min)
      min = item;
  return min + a[row][col];
}

int MinDownPath(const std::vector<std::vector<int>>& a, int maxDiff)
{
  mDiff = maxDiff;
  if (a.size() == 0)
    return -1;

  int res = -1;
  for (int i = 0; i < a[0].size(); i++) {
    int tmp = func(a, 0, i);
    if (res == -1 or (tmp != -1 and tmp < res))
      res = tmp;
  }
  return res;
}

int main() {
  int maxDiff;
  std::cin >> maxDiff;

  int n;
  std::cin >> n;

  std::vector<std::vector<int>> a;
  for (int i = 0; i < n; ++i) {
    int m;
    std::cin >> m;

    std::vector<int> line;
    for (int j = 0; j < m; ++j) {
      int val;
      std::cin >> val;
      line.push_back(val);
    }

    a.push_back(std::move(line));
  }

  std::cout << MinDownPath(a, maxDiff);
  return 0;
}*/










/*
#include <iostream>
#include <exception>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>


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
      message << "can't build request queue #" << nextId << '\n' << "because: ";
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
*/

/*#include <iostream>
#include <exception>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>

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

RequestType GetRequestType(const RequestFromConfig& request)
{
  if (request.type == "drop")
    return RequestType::Drop;
  if (request.type == "apply")
    return RequestType::Apply;
  if (request.type == "validate")
    return RequestType::Validate;
  throw runtime_error(string("unknown type '") + request.type + "'");
}

Request BuildRequest(const vector<Requester>& availableRequesters, const RequestFromConfig& requestFromConfig)
{

  Request request;
  auto it = find_if(begin(availableRequesters), end(availableRequesters), [&](const Requester& requester)
  {return requester.name == requestFromConfig.requester; });
  if (it == end(availableRequesters))
    throw runtime_error(string("unknown requester '") + requestFromConfig.requester + "'");
  request.type = GetRequestType(requestFromConfig);
  request.ownerId = it->ownerId;
  return request;

}
struct Queue
{
  uint32_t id;
  vector<Request> requests;
};
Queue BuildRequestQueue(const vector<Requester>& availableRequesters, const vector<RequestFromConfig>& requests)
{
  static uint32_t nextId = 0;
  nextId++;
  try
  {
    Queue result;
    result.id = nextId;
    for (const auto& requestFromConfig : requests)
      result.requests.push_back(BuildRequest(availableRequesters, requestFromConfig));
    return result;
  }

  catch (...)
  {
    ostringstream message("");
    message << "can't build request queue #" << nextId;
    std::throw_with_nested(std::runtime_error(message.str()));
  }
}

void print_exception(const std::exception& e, int level = 0)
{
  cout << string(level, ' ') << (level ? "because: " : "high-level operation failed: ") << e.what() << '\n';
  try
  {
    std::rethrow_if_nested(e);
  }
  catch (const std::exception& e)
  {
    print_exception(e, level + 1);
  }
  catch (...) {}
}
void PrintTaskResult(const vector<Requester>& availableRequesters, const vector<RequestFromConfig>& requests)
{
  try
  {
    auto queue = BuildRequestQueue(availableRequesters, requests);
    for (const auto& request : queue.requests)
      cout << "request in queue #" << queue.id << ": " << static_cast<int>(request.type) << " / " << request.ownerId << endl;
  }
  catch (const std::exception& ex)
  {
    print_exception(ex);
  }
  cout << endl << endl;
}*/

///////////////////////////////////////////////////////////////////////////////

// int main() // examples
// {
//   PrintTaskResult(
//       { { "first_requester", 1 }, { "second_requester", 2 }, { "third_requester", 3 } },
//       { { "Johny", "second_requester", "drop" }, { "Sam", "second_requester", "apply" }, { "Louise", "first_requester", "apply" } });
//   /* [output]
//
//   request in queue #1: 0 / 2
//   request in queue #1: 1 / 2
//   request in queue #1: 1 / 1
//
//   */
//   PrintTaskResult(
//       { { "second_requester", 2 }, { "third_requester", 3 } },
//       { { "Johny", "second_requester", "drop" }, { "Sam", "second_requester", "apply" }, { "Louise", "first_requester", "apply" } });
//   /* [output]
//
//   high-level operation failed: can't build request queue #2
//    because: unknown requester 'first_requester'
//   */
//
//   PrintTaskResult(
//       { { "first_requester", 1 }, { "second_requester", 2 }, { "third_requester", 3 } },
//       { { "Johny", "third_requester", "drop" }, { "Sam", "third_requester", "apply" }, { "Louise", "first_requester", "apply" } });
//
//   /* [output]
//   request in queue #3: 0 / 3
//   request in queue #3: 1 / 3
//   request in queue #3: 1 / 1
//   */
//
//   PrintTaskResult(
//       { { "first_requester", 1 }, { "second_requester", 2 }, { "third_requester", 3 } },
//       { { "Johny", "second_requester", "drop" }, { "Sam", "second_requester", "apply" }, { "Louise", "first_requester", "reapply" } });
//   /* [output]
//   high-level operation failed: can't build request queue #4
//    because: unknown type 'reapply'
//   */
//   return 0;
// }



/*#include <iostream>

#include <vector>

int calc(int i, int j) {
  if (i == j)
    return i;
  if (i > j) {
    int tmp = j;
    j = i;
    i = tmp;
  }
  if (i == 0 and j == 1)
    return 2;
  if (i == 0 and j == 2)
    return 1;
  if (i == 1 and j == 2)
    return 0;
}

int main() {
  std::vector<int> numbers;

  char tmp;
  while (std::cin >> tmp) {
    if (tmp == 'A')
      numbers.push_back(0);
    else if (tmp == 'B')
      numbers.push_back(1);
    else if (tmp == 'C')
      numbers.push_back(2);
  }

  while (numbers.size() > 1) {
    for (int i = 0; i < numbers.size(); i++)
      numbers[i] = calc(numbers[i], numbers[i + 1]);
    numbers.pop_back();
  }

  char res = 'A';
  if (numbers[0] == 1)
    res = 'B';
  if (numbers[0] == 2)
    res = 'C';

  std::cout << res;

  return 0;
}*/









/*#include <iostream>

#include <vector>
#include <algorithm>


int find_max(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
  auto max = std::max_element(begin, end);
  int dist = std::distance(begin, end);
  if (*max <= dist + 1) {
    return dist + 1;
  }
  int left = 0;
  int right = 0;
  if (begin != max)
    left = find_max(begin, max);
  if (end != max + 1)
    right = find_max(max + 1, end);
  if (left >= right)
    return left;
  else
    return right;
}

int main() {
  std::vector<int> numbers;

  int tmp;
  while (std::cin >> tmp)
    numbers.push_back(tmp);

  std::vector<int> modules;

  for (int i = 0; i < numbers.size() - 1; i++)
    modules.push_back(std::abs(numbers[i] - numbers[i + 1]));

  auto res = find_max(modules.begin(), modules.end());

  std::cout << res;

  return 0;
}*/
