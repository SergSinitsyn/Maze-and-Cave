#include "cave.h"

#include <fstream>
#include <random>
#include <tuple>

Cave::Cave(size_t rows, size_t cols, int density) : Model(rows, cols) {
  Generate(rows, cols, density);
}

void Cave::Generate(size_t rows, size_t cols, int density) {
  srand(time(nullptr));
  SetSize({rows, cols});
  for (size_t i = 0; i < rows_; ++i) {
    for (size_t j = 0; j < cols_; ++j) {
      board_[i][j].SetUp(i, j, (rand() % 100) < density);
    }
  }
}

int Cave::CountLiveNeighbors(int row, int col) {
  int live_neighbors = 0;
  int num_rows = rows_;
  int num_cols = cols_;
  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      if (dx == 0 && dy == 0) continue;
      int new_row = row + dx;
      int new_col = col + dy;
      if (new_row < 0 || new_row >= num_rows || new_col < 0 ||
          new_col >= num_cols || board_[new_row][new_col].life()) {
        live_neighbors++;
      }
    }
  }
  return live_neighbors;
}

void Cave::MakeOneTurn(int live_threshold, int dead_threshold) {
  CaveMatrix new_board(rows_, std::vector<CaveCell>(cols_));
  live_threshold_ = live_threshold;
  dead_threshold_ = dead_threshold;

  for (size_t i = 0; i < rows_; ++i) {
    for (size_t j = 0; j < cols_; ++j) {
      int live_neighbors = CountLiveNeighbors(i, j);
      new_board[i][j] = board_[i][j];
      if (board_[i][j].life()) {
        if (live_neighbors < dead_threshold_) {
          new_board[i][j].SetUp(i, j, false);
        }
      } else {
        if (live_neighbors > live_threshold_) {
          new_board[i][j].SetUp(i, j, true);
        }
      }
    }
  }
  board_ = std::move(new_board);
}

void Cave::SetSize(std::pair<size_t, size_t> size) {
  Model::SetSize(size);
  board_.resize(rows_);
  for (auto& row : board_) row.resize(cols_);
};

void Cave::ReadLine(size_t& line_number, const std::string& line) {
  size_t num_size = 0;
  size_t line_index = 0;
  for (size_t col_index = 0; col_index < cols_; ++col_index) {
    bool life = std::stoi(&line.at(line_index), &num_size);
    board_.at(line_number).at(col_index).SetUp(line_number, col_index, life);
    line_index += num_size;
  }
}
