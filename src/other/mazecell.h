#ifndef MAZE_OTHER_MAZECELL_H_
#define MAZE_OTHER_MAZECELL_H_

#include <cmath>

#include "cell.h"

class MazeCell : public Cell {
 public:
  MazeCell(size_t row, size_t col, bool right_wall, bool bottom_wall)
      : Cell(row, col), right_wall_(right_wall), bottom_wall_(bottom_wall) {}
  MazeCell()
      : Cell(0, 0), right_wall_(false), bottom_wall_(false), set_number_(0) {}
  MazeCell(bool right_wall, bool bottom_wall)
      : Cell(0, 0),
        right_wall_(right_wall),
        bottom_wall_(bottom_wall),
        set_number_(0) {}

  void set_right_wall(bool right_wall) { right_wall_ = right_wall; }
  void set_bottom_wall(bool bottom_wall) { bottom_wall_ = bottom_wall; }
  bool right_wall() const { return right_wall_; }
  bool bottom_wall() const { return bottom_wall_; }

  size_t set_number() const { return set_number_; }
  void set_set_number(size_t set_number) { set_number_ = set_number; }

 private:
  bool right_wall_;
  bool bottom_wall_;
  size_t set_number_{0};
};

#endif  // MAZE_OTHER_MAZECELL_H_