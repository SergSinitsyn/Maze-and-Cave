#ifndef MAZE_MODEL_MAZE_MAZE_H_
#define MAZE_MODEL_MAZE_MAZE_H_

#include <string>
#include <vector>

#include "../../other/maze_matrix.h"
#include "../model.h"

class Maze : public Model {
 public:
  Maze();
  Maze(size_t rows, size_t cols);

  ~Maze();

  size_t rows() const;
  size_t cols() const;
  void GenerationMaze(size_t rows, size_t cols);
  //! теперь находится в базовом классе
  // void ReadFile(const std::string& filename);
  void WriteFile(const std::string& filename);
  MazeMatrix& maze_matrix() { return maze_matrix_; }
  std::vector<Cell> FindPath(Cell start, Cell end);

 private:
  //! теперь находится в базовом классе
  // const size_t kMinCol = 2;
  // const size_t kMinRow = 2;
  // const size_t kMaxCol = 50;
  // const size_t kMaxRow = 50;
  const size_t kEmpty = 0;

  void ClearMatrix();
  void CopyPrewRow(size_t row);
  size_t CountSetNumberNotBottomWall(size_t curr_row, size_t curr_set_num);
  void MakeLastRow();
  std::vector<Cell> MakePathVector(std::vector<std::vector<Cell>>& prev,
                                   Cell start, Cell end);
  bool RandomBool();
  void ReadLine(size_t& line_number, const std::string& line) override;
  void SetSize(std::pair<size_t, size_t> size) override;
  //! теперь находится в базовом классе
  // void ReadSize(const std::string& line);
  void ResetSetNumber(size_t row);
  void SetBottomWall(size_t row);
  void SetRightWall(size_t row);
  void SetUniqSetNumber(size_t row);
  void UnionSet(size_t row);
  void UnionSetNumber(size_t row, size_t index);
  size_t UniqSetNumber();

  //! теперь находится в базовом классе
  // size_t rows_;
  // size_t cols_;
  size_t count_set_number_;
  MazeMatrix maze_matrix_;
};
#endif  // MAZE_MODEL_MAZE_MAZE_H_
