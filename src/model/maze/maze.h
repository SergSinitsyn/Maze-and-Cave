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

  void GenerationMaze(size_t rows, size_t cols);
  void WriteFile(const std::string& filename);
  MazeMatrix& maze_matrix() { return maze_matrix_; }
  std::vector<Cell> FindPath(Cell start, Cell end);

 private:
  const size_t kEmpty = 0;

  void ClearMatrix();
  void CopyPrewRow(size_t row);
  size_t CountSetNumberNotBottomWall(size_t curr_row, size_t curr_set_num);
  void MakeLastRow();
  std::vector<Cell> MakePathVector(const std::vector<std::vector<Cell>>& prev,
                                   Cell start, Cell end);
  bool RandomBool();
  void ReadLine(size_t& line_number, const std::string& line) override;
  void SetSize(std::pair<size_t, size_t> size) override;
  void ResetSetNumber(size_t row);
  void SetBottomWall(size_t row);
  void SetRightWall(size_t row);
  void SetUniqSetNumber(size_t row);
  void UnionSet(size_t row);
  void UnionSetNumber(size_t row, size_t index);
  size_t UniqSetNumber();

  size_t count_set_number_;
  MazeMatrix maze_matrix_;
};
#endif  // MAZE_MODEL_MAZE_MAZE_H_
