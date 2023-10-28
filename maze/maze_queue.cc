#include <cstdlib>
#include <deque>
#include <iostream>
#include <vector>

using Maze = std::vector<std::vector<int>>;
using Coordinates = std::pair<int, int>;
using PathMaze = std::vector<std::vector<Coordinates>>;

int main() {
  int rows{}, cols{};
  std::cin >> rows >> cols;
  Coordinates start{1, 1};
  Coordinates end{rows, cols};
  Maze maze(rows + 2, std::vector<int>(cols + 2, 1));
  PathMaze pathMaze(rows + 2, std::vector<Coordinates>(cols + 2));

  for (int i{1}; i < rows + 1; i++) {
    for (int j{1}; j < cols + 1; j++) {
      std::cin >> maze[i][j];
    }
  }

  std::deque<Coordinates> queue{};
  queue.push_back(start);
  maze[1][1] = 1;

  while (not queue.empty()) {
    Coordinates currentCell = queue.front();

    // end
    if (currentCell == end) {
      while (Coordinates{currentCell.first, currentCell.second} !=
             Coordinates{0, 0}) {
        auto [row, col] = currentCell;
        std::cout << "(" << row << "," << col << ")"
                  << "\n";
        currentCell = pathMaze[row][col];
      }
      exit(EXIT_SUCCESS);
    }

    auto [row, col] = currentCell;
    // 检查 maze对应坐标是否为1, 需要8个方向, 双重for
    for (auto r : {-1, 0, 1}) {
      for (auto l : {-1, 0, 1}) {
        auto nrow = row + r;
        auto ncol = col + l;
        if (maze[nrow][ncol] == 0) {
          queue.push_back({nrow, ncol});
          maze[nrow][ncol] = 1;
          pathMaze[nrow][ncol] = {row, col};
        }
      }
    }

    queue.pop_front();
  }
  exit(EXIT_FAILURE);
}
