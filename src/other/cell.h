#ifndef MAZE_OTHER_CELL_H_
#define MAZE_OTHER_CELL_H_

#include <cmath>

class Cell {
 public:
   Cell() : row_(0), col_(0) {}
  Cell(size_t row, size_t col) : row_(row), col_(col) {}

  void set_row(int row) { row_ = row; }
  void set_col(int col) { col_ = col; }
  size_t row() const { return row_; }
  size_t col() const { return col_; }

  bool operator!=(const Cell& other) const {
    return row_ != other.row_ || col_ != other.col_;
  }
   bool operator==(const Cell& other) const {
    return row_ == other.row_ && col_ == other.col_;
  }

 protected:
  size_t row_;
  size_t col_;
};

#endif  // MAZE_OTHER_CELL_H_