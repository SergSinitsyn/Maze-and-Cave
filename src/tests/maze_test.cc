#include "../model/maze/maze.h"

#include <gtest/gtest.h>

#include <fstream>

#include "../model/cave/cave.h"

bool CompareFiles(const std::string& file1, const std::string& file2) {
  std::ifstream stream1(file1);
  std::ifstream stream2(file2);

  char char1, char2;
  while (stream1.get(char1) && stream2.get(char2)) {
    if (char1 != char2) {
      stream1.close();
      stream2.close();
      return false;
    }
  }
  stream1.close();
  stream2.close();
  return true;
}

TEST(Maze, ReadFile_File_missing) {
  try {
    Maze maze;
    std::string file_name = "bad_file.txt";
    maze.ReadFile(file_name);
  } catch (const std::invalid_argument& e) {
    std::string expected_error = "File read error. The file is missing.";
    ASSERT_STREQ(expected_error.c_str(), e.what());
  }
}
TEST(Maze, ReadFile_File_empty) {
  try {
    Maze maze;
    std::string file_name = "maze-samples/maze_empty.mze";
    maze.ReadFile(file_name);
  } catch (const std::invalid_argument& e) {
    std::string expected_error = "File read error. The file is empty.";
    ASSERT_STREQ(expected_error.c_str(), e.what());
  }
}

TEST(Maze, ReadFile_bad) {
  Maze maze;
  std::string file_name = "maze-samples/maze1x1.mze";
  ASSERT_ANY_THROW(maze.ReadFile(file_name));
}

TEST(Maze, ReadFile) {
  Maze maze;
  std::string file_name = "maze-samples/maze4x4.mze";
  maze.ReadFile(file_name);
  size_t result_rows = 4;
  size_t result_cols = 4;
  Maze result_maze = Maze(result_rows, result_cols);
  ASSERT_EQ(maze.rows(), result_maze.rows());
  ASSERT_EQ(maze.cols(), result_maze.cols());

  std::vector<std::vector<bool>> result_matrix_right_wall(
      result_rows, std::vector<bool>(result_cols));
  result_matrix_right_wall = {
      {0, 0, 0, 1}, {1, 0, 1, 1}, {0, 1, 0, 1}, {0, 0, 0, 1}};
  std::vector<std::vector<int>> result_matrix_bottom_wall(
      result_rows, std::vector<int>(result_cols));
  result_matrix_bottom_wall = {
      {1, 0, 1, 0}, {0, 0, 1, 0}, {1, 1, 0, 1}, {1, 1, 1, 1}};
  MazeMatrix maze_matrix = maze.maze_matrix();
  for (size_t i = 0; i < result_rows; ++i) {
    for (size_t j = 0; j < result_cols; ++j) {
      ASSERT_EQ(maze_matrix(i, j).right_wall(), result_matrix_right_wall[i][j]);
      ASSERT_EQ(maze_matrix(i, j).bottom_wall(),
                result_matrix_bottom_wall[i][j]);
    }
  }
}

TEST(Maze, WriteFile) {
  Maze maze;
  std::string file_name = "maze-samples/maze20x20.mze";
  ASSERT_NO_THROW(maze.ReadFile(file_name));
  maze.WriteFile("test.mze");
  ASSERT_TRUE(CompareFiles("test.mze", file_name));
}

TEST(Maze, Maze_badsize_0) {
  try {
    Maze maze(10, 1);
  } catch (const std::invalid_argument& e) {
    std::string expected_error = "Error. The size is smaller than allowed.";
    ASSERT_STREQ(expected_error.c_str(), e.what());
  }
}

TEST(Maze, Maze_badsize_1) {
  try {
    Maze maze(1, 10);
  } catch (const std::invalid_argument& e) {
    std::string expected_error = "Error. The size is smaller than allowed.";
    ASSERT_STREQ(expected_error.c_str(), e.what());
  }
}

TEST(Maze, Maze_badsize_2) {
  try {
    Maze maze(51, 10);
  } catch (const std::invalid_argument& e) {
    std::string expected_error = "Error. The size exceeds the allowable.";
    ASSERT_STREQ(expected_error.c_str(), e.what());
  }
}

TEST(Maze, Maze_badsize_3) {
  try {
    Maze maze(10, 51);
  } catch (const std::invalid_argument& e) {
    std::string expected_error = "Error. The size exceeds the allowable.";
    ASSERT_STREQ(expected_error.c_str(), e.what());
  }
}

TEST(Maze, Maze_move_constructor) {
  MazeMatrix matrix;
  MazeMatrix m = std::move(matrix);
  ASSERT_ANY_THROW(MazeMatrix ma(1, 2));
  ASSERT_ANY_THROW(matrix(100, 200));
  ASSERT_ANY_THROW(matrix.set_rows(0));
  ASSERT_ANY_THROW(matrix.set_cols(0));
}

TEST(Maze, Generation_maze) {
  Maze maze;
  maze.GenerationMaze(50, 50);
  size_t result_rows = 50;
  size_t result_cols = 50;
  Maze result_maze = Maze(result_rows, result_cols);
  ASSERT_EQ(maze.rows(), result_maze.rows());
  ASSERT_EQ(maze.cols(), result_maze.cols());
}

TEST(Maze, FindPath) {
  Maze maze;
  std::string file_name = "maze-samples/maze4x4.mze";
  maze.ReadFile(file_name);
  Cell start = {0, 0};
  Cell finish = {3, 0};
  std::vector<Cell> path = maze.FindPath(start, finish);
  std::vector<Cell> path_result = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 3},
                                   {2, 3}, {2, 2}, {3, 2}, {3, 1}, {3, 0}};
  for (size_t i = 0; i < path_result.size(); ++i) {
    ASSERT_EQ(path[i].row(), path_result[i].row());
    ASSERT_EQ(path[i].col(), path_result[i].col());
  }
}

TEST(Cave, ReadFile_File_empty) {
  try {
    Cave cave(5, 5);
    std::string file_name = "maze-samples/cave_empty.cve";
    cave.ReadFile(file_name);
  } catch (const std::invalid_argument& e) {
    std::string expected_error = "File read error. The file is empty.";
    ASSERT_STREQ(expected_error.c_str(), e.what());
  }
}

TEST(Cave, ReadFile_bad) {
  Cave cave(5, 5);
  std::string file_name = "maze-samples/cave_0.cve";
  ASSERT_ANY_THROW(cave.ReadFile(file_name));
}

TEST(Cave, ReadFile_wrong_size) {
  Cave cave(5, 5);
  std::string file_name = "maze-samples/wrong_size_cave.cve";
  ASSERT_ANY_THROW(cave.ReadFile(file_name));
}

TEST(Cave, Model_ReadSize) {
  Model model(5, 5);
  std::string line = "1 0 1 0 1";
  size_t row = 0;
  ASSERT_ANY_THROW(model.ReadLine(row, line));
}

TEST(Cave, ReadFile) {
  Cave cave(5, 7);
  std::string file_name = "maze-samples/cave_1.cve";
  cave.ReadFile(file_name);
  size_t result_rows = 10;
  size_t result_cols = 10;
  Cave result_cave = Cave(result_rows, result_cols);
  EXPECT_EQ(cave.rows(), result_cave.rows());
  EXPECT_EQ(cave.cols(), result_cave.cols());

  CaveMatrix result_matrix = {
      {1, 0, 1, 0, 0, 0, 0, 1, 1, 0}, {0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
      {0, 0, 1, 0, 1, 0, 1, 1, 0, 1}, {0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
      {0, 0, 0, 1, 1, 0, 0, 1, 1, 1}, {0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
      {1, 1, 0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
      {1, 0, 0, 0, 0, 1, 1, 0, 0, 0}, {0, 1, 1, 0, 0, 1, 1, 0, 0, 0}};

  int sum = 0;
  CaveMatrix file_matrix = cave.GetMatrix();
  for (size_t i = 0; i < result_rows; ++i) {
    for (size_t j = 0; j < result_cols; ++j) {
      EXPECT_EQ(file_matrix[i][j].life(), result_matrix[i][j].life());
      sum += file_matrix[i][j].life();
    }
  }
  cave.MakeOneTurn(2, 3);
  int new_sum = 0;
  CaveMatrix new_matrix = cave.GetMatrix();
  for (size_t i = 0; i < result_rows; ++i) {
    for (size_t j = 0; j < result_cols; ++j) {
      new_sum += new_matrix[i][j].life();
    }
  }
  EXPECT_NE(sum, new_sum);
}

TEST(Cave, ReadFile25x50) {
  Cave cave(5, 7);
  std::string file_name = "maze-samples/cave25x50.cve";
  cave.ReadFile(file_name);
  size_t result_rows = 25;
  size_t result_cols = 50;
  Cave result_cave = Cave(result_rows, result_cols);
  EXPECT_EQ(cave.rows(), result_cave.rows());
  EXPECT_EQ(cave.cols(), result_cave.cols());
}

TEST(Cave, Generate) {
  const int kSize = 50;
  Cave cave(kSize, kSize);
  CaveMatrix matrix = cave.GetMatrix();
  int prev_sum = 0;
  bool have_diff = false;
  for (size_t i = 0; i < kSize; ++i) {
    int sum = 0;
    for (size_t j = 0; j < kSize; ++j) {
      sum += static_cast<int>(matrix[i][j].life());
    }
    ASSERT_TRUE(sum > 0);
    ASSERT_TRUE(sum < kSize);
    if (sum != prev_sum) {
      have_diff = true;
    }
    prev_sum = sum;
  }
  ASSERT_TRUE(have_diff);
}