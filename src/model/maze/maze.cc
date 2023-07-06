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

size_t Maze::rows() const { return rows_; }

size_t Maze::cols() const { return cols_; }

//! Дублируется с Саве
void Maze::ReadFile(const std::string& filename) {
  ClearMatrix();
  std::ifstream file(filename);
  if (!file) {
    throw std::invalid_argument("File read error. The file is missing.");
  }
  if (file.peek() == std::ifstream::traits_type::eof()) {
    throw std::invalid_argument("File read error. The file is empty.");
  }
  std::string line;
  std::getline(file, line);
  ReadSize(line);
  for (size_t i = 0; i < rows_ * 2; ++i) {
    std::getline(file, line);
    if (!line.empty()) {
      ReadMatrixLine(i, line);
    } else {
      --i;
    }
  }
  file.close();
}

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

void Maze::ReadMatrixLine(size_t& line_number, const std::string& line) {
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

//! Дублируется с Саве
void Maze::ReadSize(const std::string& line) {
  size_t pos = 0;
  size_t rows = std::stoi(&line.at(pos), &pos);
  size_t cols = std::stoi(&line.at(pos));
  if (rows <= kMinRow || cols <= kMinCol || rows > kMaxRow || cols > kMaxCol) {
    throw std::invalid_argument(
        "File read error. The dimensions of the maze are not correct.");
  }
  maze_matrix_ = MazeMatrix(rows, cols);
  rows_ = rows;
  cols_ = cols;
}

std::vector<Cell> Maze::MakePathVector(std::vector<std::vector<Cell>>& prev,
                                       Cell start, Cell end) {
  std::vector<Cell> path;
  Cell current_point = end;
  while (current_point != start) {
    path.push_back(current_point);
    current_point = prev[current_point.row()][current_point.col()];
  }
  path.push_back(start);
  std::reverse(path.begin(), path.end());
  return path;
}

std::vector<Cell> Maze::FindPath(Cell start, Cell end) {
  std::vector<std::vector<bool>> visited(rows_,
                                         std::vector<bool>(cols_, false));
  std::queue<Cell> q;
  std::vector<std::vector<Cell>> prev(rows_, std::vector<Cell>(cols_));
  std::vector<Cell> path{};

  q.push(start);
  visited[start.row()][start.col()] = true;

  while (!q.empty()) {
    Cell current_point = q.front();
    q.pop();

    if (current_point == end) {
      path = MakePathVector(prev, start, end);
      break;
    }

    // Проверяем соседние клетки
    int delta_row[] = {-1, 1, 0, 0};
    int delta_column[] = {0, 0, -1, 1};
    for (size_t i = 0; i < 4; i++) {
      size_t new_row = current_point.row() + delta_row[i];
      size_t new_col = current_point.col() + delta_column[i];

      if (maze_matrix_.IsValid(new_row, new_col) &&
          maze_matrix_.MovePossible(current_point, new_row, new_col) &&
          !visited[new_row][new_col]) {
        q.push({new_row, new_col});
        visited[new_row][new_col] = true;
        prev[new_row][new_col] = current_point;
      }
    }
  }

  return path;
}
