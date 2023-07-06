#include <random>

#include "maze.h"

void Maze::GenerationMaze(size_t rows, size_t cols) {
  ClearMatrix();
  rows_ = rows;
  cols_ = cols;
  maze_matrix_ = MazeMatrix(rows, cols);
  for (size_t i = 0; i < rows_; ++i) {
    CopyPrewRow(i);
    ResetSetNumber(i);
    SetUniqSetNumber(i);
    SetRightWall(i);
    UnionSet(i);
    SetBottomWall(i);
  }
  MakeLastRow();
}

void Maze::CopyPrewRow(size_t row) {
  if (row > 0) {
    for (size_t j = 0; j < cols_; ++j) {
      maze_matrix_(row, j).set_set_number(
          maze_matrix_(row - 1, j).set_number());
    }
  }
}

size_t Maze::CountSetNumberNotBottomWall(size_t curr_row, size_t curr_set_num) {
  size_t count = 0;
  for (size_t j = 0; j < cols_; ++j) {
    if (maze_matrix_(curr_row, j).set_number() == curr_set_num &&
        maze_matrix_(curr_row, j).bottom_wall() == false) {
      count++;
    }
  }
  return count;
}

bool Maze::RandomBool() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, 1);
  return dist(gen);
}

void Maze::MakeLastRow() {
  size_t row = rows_ - 1;
  for (size_t j = 0; j < cols_ - 1; ++j) {
    if (maze_matrix_(row, j).right_wall() == true &&
        maze_matrix_(row, j).set_number() !=
            maze_matrix_(row, j + 1).set_number()) {
      maze_matrix_(row, j).set_right_wall(false);
      UnionSetNumber(row, j);
    }
  }
}

void Maze::ResetSetNumber(size_t row) {
  if (row > 0) {
    for (size_t j = 0; j < cols_; ++j) {
      if (maze_matrix_(row - 1, j).bottom_wall() == 1)
        maze_matrix_(row, j).set_set_number(kEmpty);
    }
  }
}

void Maze::SetBottomWall(size_t row) {
  for (size_t j = 0; j < cols_; ++j) {
    if (row == rows_ - 1) {
      maze_matrix_(row, j).set_bottom_wall(true);
    } else if (CountSetNumberNotBottomWall(
                   row, maze_matrix_(row, j).set_number()) > 1) {
      maze_matrix_(row, j).set_bottom_wall(RandomBool());
    } else {
      maze_matrix_(row, j).set_bottom_wall(false);
    }
  }
}

void Maze::SetRightWall(size_t row) {
  for (size_t j = 0; j < cols_ - 1; ++j) {
    maze_matrix_(row, j).set_right_wall(RandomBool());
  }
  maze_matrix_(row, cols_ - 1).set_right_wall(true);
}

void Maze::SetUniqSetNumber(size_t row) {
  for (size_t j = 0; j < cols_; ++j) {
    if (maze_matrix_(row, j).set_number() == kEmpty)
      maze_matrix_(row, j).set_set_number(UniqSetNumber());
  }
}

void Maze::UnionSet(size_t row) {
  for (size_t j = 0; j < cols_ - 1; ++j) {
    size_t curr_num = maze_matrix_(row, j).set_number();
    size_t next_num = maze_matrix_(row, j + 1).set_number();
    if (curr_num != next_num && maze_matrix_(row, j).right_wall() == false) {
      UnionSetNumber(row, j);
    } else {
      maze_matrix_(row, j).set_right_wall(true);
    }
  }
}

void Maze::UnionSetNumber(size_t row, size_t index) {
  size_t curr_num = maze_matrix_(row, index).set_number();
  size_t next_num = maze_matrix_(row, index + 1).set_number();
  for (size_t k = 0; k < cols_; ++k) {
    if (maze_matrix_(row, k).set_number() == next_num) {
      maze_matrix_(row, k).set_set_number(curr_num);
    }
  }
}

size_t Maze::UniqSetNumber() { return size_t(count_set_number_++); }