#include "maze_matrix.h"

#include <algorithm>
#include <cstring>
#include <iostream>

constexpr size_t kMinDimensions = 2;

MazeMatrix::MazeMatrix() : MazeMatrix(kMinDimensions, kMinDimensions) {}

MazeMatrix::MazeMatrix(size_t rows, size_t cols) {
  if (rows < kMinDimensions || cols < kMinDimensions) {
    throw std::invalid_argument("Incorrect parameters");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = new MazeCell[rows * cols];
}

MazeMatrix::MazeMatrix(const MazeMatrix& other) {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new MazeCell[rows_ * cols_];
    std::memcpy(matrix_, other.matrix_,
                other.rows_ * other.cols_ * sizeof(MazeCell));
  }
}

MazeMatrix::MazeMatrix(MazeMatrix&& other) {
  if (this != &other) {
    matrix_ = other.matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    other.matrix_ = nullptr;
  }
}

MazeMatrix& MazeMatrix::operator=(const MazeMatrix& x) {
  if (this != &x) {
    rows_ = x.rows_;
    cols_ = x.cols_;
    delete[] matrix_;
    matrix_ = new MazeCell[x.rows_ * x.cols_];
    std::memcpy(matrix_, x.matrix_, x.rows_ * x.cols_ * sizeof(MazeCell));
  }
  return *this;
}

MazeCell& MazeMatrix::operator()(const size_t i, const size_t j) {
  if (i > rows_ || j > cols_) {
    throw std::invalid_argument("Incorrect parameters");
  }
  return matrix_[i * cols_ + j];
}

MazeMatrix::~MazeMatrix() {
  if (matrix_ != nullptr) delete[] matrix_;
}

void MazeMatrix::ClearMatrix() noexcept { *this = {}; }

size_t MazeMatrix::rows() const { return rows_; }

size_t MazeMatrix::cols() const { return cols_; }

void MazeMatrix::set_rows(size_t new_rows) {
  if (new_rows == 0) {
    throw std::invalid_argument("Incorrect parameters");
  }
  MazeMatrix result(new_rows, cols_);
  size_t copy_rows = std::min(new_rows, rows_);
  std::memcpy(result.matrix_, matrix_, copy_rows * cols_ * sizeof(MazeCell));
  if (new_rows > rows_) {
    std::fill(result.matrix_ + rows_ * result.cols_,
              result.matrix_ + new_rows * result.cols_, MazeCell());
  }
  *this = std::move(
      result);  // избегаем копирования, увеличиваем производительность
}

void MazeMatrix::set_cols(const size_t new_cols) {
  if (new_cols == 0) {
    throw std::invalid_argument("Incorrect parameters");
  }
  MazeMatrix result(rows_, new_cols);
  for (size_t i = 0; i < result.rows_; i++) {
    std::memcpy(&result.matrix_[i * result.cols_], &matrix_[i * cols_],
                cols_ * sizeof(MazeCell));
    if (new_cols > cols_) {
      std::fill(result.matrix_ + i * result.cols_ + cols_,
                result.matrix_ + i * result.cols_ + new_cols, MazeCell());
    }
  }
  *this = std::move(
      result);  // избегаем копирования, увеличиваем производительность
}

void MazeMatrix::SetDimensions(const size_t new_rows, const size_t new_cols) {
  set_cols(new_cols);
  set_rows(new_rows);
}

bool MazeMatrix::IsValid(const size_t row, const size_t col) const {
  return (row < rows_ && col < cols_);
}

/**
 * Get the direction of movement based on the current point and new row and
 * column. Only one step is allowed, no diagonal movement
 *
 * @param current_point the current point
 * @param new_row the new row
 * @param new_col the new column
 *
 * @return the direction of movement
 *
 * @throws None
 */
MazeMatrix::Direction MazeMatrix::GetDirection(const Cell current_point,
                                               const int new_row,
                                               const int new_col) const {
  Direction d;
  int row_diff = static_cast<int>(current_point.row()) - new_row;
  int col_diff = static_cast<int>(current_point.col()) - new_col;
  if (row_diff < 0) {
    d = Direction::kDown;
  } else if (row_diff > 0) {
    d = Direction::kUp;
  } else if (col_diff < 0) {
    d = Direction::kRight;
  } else if (col_diff > 0) {
    d = Direction::kLeft;
  }
  return d;
}

/**
 * Checks if a move from the current point to a new row and column is possible.
 * Only one step is allowed. No new_row or new_col validation performed
 *
 * @param current_point the current point on the wall matrix
 * @param new_row the new row to move to
 * @param new_col the new column to move to
 *
 * @return true if the move is possible, false otherwise
 *
 * @throws None
 */
bool MazeMatrix::MovePossible(const Cell current_point, const int new_row,
                              const int new_col) const {
  bool move_possible = false;
  MazeMatrix matrix = *this;
  Direction direction = GetDirection(current_point, new_row, new_col);
  if (direction == Direction::kRight) {
    move_possible =
        matrix(current_point.row(), current_point.col()).right_wall() == 0;
  } else if (direction == Direction::kDown) {
    move_possible =
        matrix(current_point.row(), current_point.col()).bottom_wall() == 0;
  } else if (direction == Direction::kLeft) {
    move_possible = matrix(new_row, new_col).right_wall() == 0;
  } else if (direction == Direction::kUp) {
    move_possible = matrix(new_row, new_col).bottom_wall() == 0;
  }

  return move_possible;
}
