#include "maze.h"

#include <algorithm>
#include <fstream>
#include <ostream>
#include <queue>

Maze::Maze() : count_set_number_(1), maze_matrix_() {
  cols_ = maze_matrix_.cols();
  rows_ = maze_matrix_.rows();
}

Maze::Maze(size_t rows, size_t cols) : Maze() {
  if (rows <= kMinRow || cols <= kMinCol) {
    throw std::invalid_argument("Error. The size is smaller than allowed.");
  }
  if (cols > kMaxCol || rows > kMaxRow) {
    throw std::invalid_argument("Error. The size exceeds the allowable.");
  }
  rows_ = rows;
  cols_ = cols;
  maze_matrix_.SetDimensions(rows, cols);
}

Maze::~Maze() {}

void Maze::WriteFile(const std::string& filename) {
  std::ofstream file(filename);
  if (!file) throw std::runtime_error("File write error. The file is missing.");
  file << rows_ << ' ' << cols_ << '\n';
  for (size_t i = 0; i < rows_; ++i) {
    for (size_t j = 0; j < cols_; ++j) {
      file << maze_matrix_(i, j).right_wall();
      if (j < cols_ - 1) file << ' ';
    }
    file << '\n';
  }
  file << '\n';
  for (size_t i = 0; i < rows_; ++i) {
    for (size_t j = 0; j < cols_; ++j) {
      file << maze_matrix_(i, j).bottom_wall();
      if (j < cols_ - 1) file << ' ';
    }
    file << '\n';
  }
  file.close();
}

void Maze::ClearMatrix() { maze_matrix_.ClearMatrix(); }

void Maze::SetSize(std::pair<size_t, size_t> size) {
  std::tie(rows_, cols_) = size;
  lines_to_read_ = rows_ * 2;
  maze_matrix_ = MazeMatrix(rows_, cols_);
};

void Maze::ReadLine(size_t& line_number, const std::string& line) {
  size_t num_size = 0;
  size_t line_index = 0;
  for (size_t col_index = 0; col_index < cols_; ++col_index) {
    bool wall = std::stoi(&line.at(line_index), &num_size);
    if (line_number < rows_) {
      maze_matrix_(line_number, col_index).set_right_wall(wall);
    } else {
      maze_matrix_(line_number - rows_, col_index).set_bottom_wall(wall);
    }
    line_index += num_size;
  }
}

std::vector<Cell> Maze::MakePathVector(
    const std::vector<std::vector<Cell>>& previous, Cell start, Cell end) {
  std::vector<Cell> path;
  for (Cell current = end; current != start;
       current = previous[current.row()][current.col()]) {
    path.push_back(current);
  }
  path.push_back(start);
  std::reverse(path.begin(), path.end());
  return path;
}

std::vector<Cell> Maze::FindPath(Cell start, Cell end) {
  std::vector<std::vector<bool>> visited(rows_,
                                         std::vector<bool>(cols_, false));
  std::queue<Cell> q;
  std::vector<std::vector<Cell>> previous(rows_, std::vector<Cell>(cols_));
  std::vector<Cell> path{};

  q.push(start);
  visited[start.row()][start.col()] = true;

  while (!q.empty()) {
    Cell current = q.front();
    q.pop();

    if (current == end) {
      path = MakePathVector(previous, start, end);
      break;
    }

    const int delta_row[] = {-1, 1, 0, 0};
    const int delta_column[] = {0, 0, -1, 1};
    for (size_t i = 0; i < 4; i++) {
      size_t new_row = current.row() + delta_row[i];
      size_t new_col = current.col() + delta_column[i];

      if (maze_matrix_.IsValid(new_row, new_col) &&
          maze_matrix_.MovePossible(current, new_row, new_col) &&
          !visited[new_row][new_col]) {
        q.push({new_row, new_col});
        visited[new_row][new_col] = true;
        previous[new_row][new_col] = current;
      }
    }
  }

  return path;
}
