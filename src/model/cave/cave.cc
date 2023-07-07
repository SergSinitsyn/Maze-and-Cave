#include "cave.h"

#include <fstream>
#include <random>
#include <tuple>

Cave::Cave(size_t rows, size_t cols, int density) : Model(rows, cols) {
  srand((unsigned)time(NULL));
  SetSize({rows, cols});
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      board_[i][j].SetUp(i, j, (rand() % 100) < density);
    }
  }
}

int Cave::CountLiveNeighbors(int row, int col) {
  int live_neighbors = 0;
  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      if (dx == 0 && dy == 0) continue;

      int ni = row + dx;
      int nj = col + dy;

      if (ni >= 0 && ni < rows_ && nj >= 0 && nj < cols_ &&
          board_[ni][nj].life()) {
        live_neighbors++;
      }
    }
  }
  return live_neighbors;
}

void Cave::MakeOneTurn() {
  CaveMatrix new_board(rows_, std::vector<CaveCell>(cols_));

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      int live_neighbors = CountLiveNeighbors(i, j);
      // Apply the rules of the game
      if (board_[i][j].life()) {
        if (live_neighbors < dead_treshold_) {
          new_board[i][j].SetUp(i, j, false);  // Cell become dead
        }
      } else {
        if (live_neighbors > live_treshold_) {
          new_board[i][j].SetUp(i, j, true);  // Cell is born
        }
      }
    }
  }

  // Update the original board
  board_ = new_board;
}

void Cave::SetSize(std::pair<size_t, size_t> size) {
  Model::SetSize(size);
  board_.resize(rows_, std::vector<CaveCell>(cols_));
};

void Cave::ReadLine(size_t& line_number, const std::string& line) {
  size_t num_size = 0;
  size_t line_index = 0;
  for (size_t col_index = 0; col_index < cols_; ++col_index) {
    bool life = std::stoi(&line.at(line_index), &num_size);
    board_[line_number][col_index].SetUp(line_number, col_index,
                                         !life);  //! 1 is dead cell in file
    line_index += num_size;
  }
}
