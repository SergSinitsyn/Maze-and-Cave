#ifndef CAVE_H
#define CAVE_H
#include <vector>

class Cave {
 public:
  Cave();
  void MakeOneTurn();

 protected:
  int CountLiveNeighbors(int row, int col);

  std::vector<std::vector<int>> board_;
  int live_treshold_ = 2;
  int dead_treshold_ = 3;
  int rows_;
  int cols_;
};

#endif  // CAVE_H
