#ifndef MAZE_OTHER_CAVECELL_H_
#define MAZE_OTHER_CAVECELL_H_

#include <cmath>

#include "cell.h"

class CaveCell : public Cell {
 public:
  CaveCell(size_t row, size_t col, bool life_) : Cell(row, col), life_(life_) {}

  void set_life(bool life) { life_ = life; }
  bool life() const { return life_; }

 private:
  bool life_;
};

#endif  // MAZE_OTHER_CAVECELL_H_