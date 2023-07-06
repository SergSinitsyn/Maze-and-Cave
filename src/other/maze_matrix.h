#ifndef MAZE_OTHER_MAZE_MATRIX_H_
#define MAZE_OTHER_MAZE_MATRIX_H_

#include "mazecell.h"

// сделвать класс матриц шаблонным

class MazeMatrix {
 public:
  MazeMatrix();
  MazeMatrix(size_t rows, size_t cols);
  MazeMatrix(const MazeMatrix& other);
  MazeMatrix(MazeMatrix&& other);

  MazeMatrix& operator=(const MazeMatrix& x);
  MazeCell& operator()(const size_t i, const size_t j);

  ~MazeMatrix();

  void ClearMatrix() noexcept;
  size_t rows() const;
  size_t cols() const;
  void set_rows(const size_t new_rows);
  void set_cols(const size_t new_cols);
  void SetDimensions(const size_t new_rows, const size_t new_cols);
  bool MovePossible(const Cell current_point, const int new_row,
                    const int new_col) const;
  bool IsValid(const size_t new_row, const size_t new_col) const;
  enum Direction { kUp, kDown, kLeft, kRight };
  Direction GetDirection(const Cell current_point, const int new_row,
                         const int new_col) const;

 private:
  size_t rows_, cols_;
  MazeCell* matrix_;
};

#endif  // MAZE_OTHER_MAZE_MATRIX_H_