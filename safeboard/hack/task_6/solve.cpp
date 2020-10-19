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

