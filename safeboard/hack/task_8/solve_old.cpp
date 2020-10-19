#include <iostream>
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
}

