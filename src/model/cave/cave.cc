#include "cave.h"

Cave::Cave() {
  //! TODO initalize board
  rows_ = board_.size();
  cols_ = board_[0].size();
};

int Cave::CountLiveNeighbors(int row, int col) {
  int live_neighbors = 0;
  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      if (dx == 0 && dy == 0) continue;

      int ni = row + dx;
      int nj = col + dy;

      if (ni >= 0 && ni < rows_ && nj >= 0 && nj < cols_ && board_[ni][nj]) {
        live_neighbors++;
      }
    }
  }
  return live_neighbors;
}

void Cave::MakeOneTurn() {
  std::vector<std::vector<int>> new_board(rows_, std::vector<int>(cols_, 0));

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      int live_neighbors = CountLiveNeighbors(i, j);
      // Apply the rules of the game
      if (board_[i][j]) {
        if (live_neighbors < dead_treshold_) {
          new_board[i][j] = 0;  // Cell become dead
        }
      } else {
        if (live_neighbors > live_treshold_) {
          new_board[i][j] = 1;  // Cell is born
        }
      }
    }
  }

  // Update the original board
  board_ = new_board;
}
