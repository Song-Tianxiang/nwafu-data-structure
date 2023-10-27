#include <cstddef> // size_t
#include <cstdlib>
#include <iostream>
#include <utility> // pair
#include <vector>

using std::cin;
using std::cout;

struct Cell;
using Coordinates = std::pair<size_t, size_t>;
using Cells = std::vector<Cell>;
using Maze = std::vector<std::vector<int>>;

struct Cell {
  Coordinates coordinates{};
  enum Direction {
    Down,
    Left,
    Up,
    Right,
    NoLeftDirection,
  } direction{Down};

  Cell() = default;
  Cell(Coordinates coordinates_, Direction direction_ = Down)
      : coordinates{coordinates_}, direction{direction_} {}

  friend std::ostream &operator<<(std::ostream &os, const Cell &cell) {
    os << cell.coordinates.second << " " << cell.coordinates.first << " ";
    return os;
  }
};

void step(Maze &&maze, Cells &&cells) {
  auto top = cells.back();

  Cell currentCell{};
  switch (top.direction) {
  case Cell::Down:
    if (currentCell.coordinates.first + 1 < maze.size()) {
      currentCell = {{top.coordinates.first + 1, top.coordinates.second}};
      break;
    }
  case Cell::Left:
    if (currentCell.coordinates.second - 1 < maze[0].size()) {
      currentCell = {{top.coordinates.first, top.coordinates.second - 1}};
      break;
    }
  case Cell::Up:
    if (currentCell.coordinates.first - 1 < maze.size()) {
      currentCell = {{top.coordinates.first - 1, top.coordinates.second}};
      break;
    }
  case Cell::Right:
    if (currentCell.coordinates.second+1 < maze[0].size()) {
      currentCell = {{top.coordinates.first, top.coordinates.second + 1}};
      break;
    }
  default:
    cells.pop_back();
    step(std::move(maze), std::move(cells));
    return;
  }

  switch (auto [row, col] = currentCell.coordinates; maze[row][col]) {
  case 4:
    cells.push_back(currentCell);
    for (const auto &cell : cells) {
      cout << cell << "\n";
    }
    exit(EXIT_SUCCESS);
  case 1:
    top.direction = static_cast<Cell::Direction>(top.direction + 1);
    break;
  case 0:
    cells.push_back(currentCell);
    break;
  }
  step(std::move(maze), std::move(cells));
}

int main() {
  size_t cols{}, rows{};
  cin >> cols >> rows;
  Maze maze(rows, std::vector<int>(cols));
  Coordinates start{};

  for (size_t i{0}; i < rows; i++) {
    for (size_t j{0}; j < cols; j++) {
      cin >> maze[i][j];
      if (maze[i][j] == 3) {
        start = {i, j};
      }
    }
  }

  Cells cells{};

  step(std::move(maze), std::move(cells));

  return 0;
}
