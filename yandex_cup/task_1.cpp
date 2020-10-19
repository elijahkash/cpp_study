#include <iostream>
#include <set>
#include <vector>

bool check(std::vector<int>& ticket, std::set<int>& winNumbers) {
  int count = 0;
  for (auto& nbr: ticket) {
    if (winNumbers.find(nbr) != winNumbers.end())
      count++;
  }
  return (count >= 3);
}

int main() {
  // std::vector<int> winNumbers;
  std::set<int> winNumbers;
  std::vector<std::vector<int>> tickets;
  for (int i = 0; i < 10; i++) {
    int input;
    std::cin >> input;
    // winNumbers.push_back(input);
    winNumbers.emplace(input);
  }
  int count;
  std::cin >> count;
  for (int i = 0; i < count; i++) {
    tickets.emplace_back();
    for (int j = 0; j < 6; j++) {
      int tmp;
      std::cin >> tmp;
      tickets[i].emplace_back(tmp);
    }
  }

  for (auto& ticket: tickets) {
    if (check(ticket, winNumbers))
      std::cout << "Lucky" << std::endl;
    else
      std::cout << "Unlucky" << std::endl;
  }

  return 0;
}

