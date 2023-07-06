#ifndef CAVE_H
#define CAVE_H
#include <string>
#include <vector>

#include "../../other/cavecell.h"
#include "../model.h"

class Cave : public Model {
 public:
  Cave(){};
  Cave(size_t rows, size_t cols) : Model(rows, cols){};
  void MakeOneTurn();

 protected:
  void ReadLine(size_t& line_number, const std::string& line) override;
  void SetSize(std::pair<size_t, size_t> size) override {
    std::tie(rows_, cols_) = size;
    lines_to_read_ = rows_;
  };
  int CountLiveNeighbors(int row, int col);

  std::vector<std::vector<CaveCell>> board_;
  int live_treshold_ = 2;
  int dead_treshold_ = 3;
};

#endif  // CAVE_H
