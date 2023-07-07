#ifndef CAVE_H
#define CAVE_H
#include <string>
#include <vector>

#include "../../other/cavecell.h"
#include "../model.h"

using CaveMatrix = std::vector<std::vector<CaveCell>>;
class Cave : public Model {
 public:
  Cave(){};
  Cave(size_t rows, size_t cols) : Model(rows, cols){};
  CaveMatrix const& GetMatrix() const { return board_; };
  void MakeOneTurn();

 protected:
  void ReadLine(size_t& line_number, const std::string& line) override;
  int CountLiveNeighbors(int row, int col);

  CaveMatrix board_;
  int live_treshold_ = 2;
  int dead_treshold_ = 3;
};

#endif  // CAVE_H
