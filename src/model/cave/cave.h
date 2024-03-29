#ifndef MAZE_MODEL_CAVE_CAVE_H
#define MAZE_MODEL_CAVE_CAVE_H
#include <string>
#include <vector>

#include "../../other/cave_matrix.h"
#include "../../other/cavecell.h"
#include "../model.h"

class Cave : public Model {
 public:
  Cave(size_t rows = 50, size_t cols = 50, int density = 50);
  void Generate(size_t rows = 50, size_t cols = 50, int density = 50);
  CaveMatrix const& GetMatrix() const { return board_; };
  void MakeOneTurn(int live, int dead);

 protected:
  void ReadLine(size_t& line_number, const std::string& line) override;
  void SetSize(std::pair<size_t, size_t> size) override;
  int CountLiveNeighbors(int row, int col);

  CaveMatrix board_;
  int live_threshold_ = 2;
  int dead_threshold_ = 3;
};

#endif  // MAZE_MODEL_CAVE_CAVE_H
