#include "../model/maze/maze.h"

#include <gtest/gtest.h>

#include <fstream>

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

TEST(Viewer, ReadFile_File_missing) {
  Maze maze;
  std::string file_name = "bad_file.txt";
  try {
    maze.ReadFile(file_name);
  } catch (const std::invalid_argument& e) {
    std::string expected_error = "File read error. The file is missing.";
    ASSERT_STREQ(expected_error.c_str(), e.what());
  }
}
TEST(Viewer, ReadFile_File_empty) {
  Maze maze;
  std::string file_name = "../data-samples/maze_empty.mze";
  try {
    maze.ReadFile(file_name);
  } catch (const std::invalid_argument& e) {
    std::string expected_error = "File read error. The file is empty.";
    ASSERT_STREQ(expected_error.c_str(), e.what());
  }
}

TEST(Viewer, ReadFile_bad) {
  Maze maze;
  std::string file_name = "../data-samples/maze1x1.mze";
  ASSERT_ANY_THROW(maze.ReadFile(file_name));
}

TEST(Viewer, ReadFile) {
  Maze maze;
  std::string file_name = "../data-samples/maze4x4.mze";
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

TEST(Viewer, WriteFile) {
  Maze maze;
  std::string file_name = "../data-samples/maze20x20.mze";
  ASSERT_NO_THROW(maze.ReadFile(file_name));
  maze.WriteFile("test.mze");
  ASSERT_TRUE(CompareFiles("test.mze", file_name));
}

TEST(Viewer, Maze_badsize_0) {
  try {
    Maze maze(10, 1);
  } catch (const std::invalid_argument& e) {
    std::string expected_error = "Error. The size is smaller than allowed.";
    ASSERT_STREQ(expected_error.c_str(), e.what());
  }
}

TEST(Viewer, Maze_badsize_1) {
  try {
    Maze maze(1, 10);
  } catch (const std::invalid_argument& e) {
    std::string expected_error = "Error. The size is smaller than allowed.";
    ASSERT_STREQ(expected_error.c_str(), e.what());
  }
}

TEST(Viewer, Maze_badsize_2) {
  try {
    Maze maze(51, 10);
  } catch (const std::invalid_argument& e) {
    std::string expected_error = "Error. The size exceeds the allowable.";
    ASSERT_STREQ(expected_error.c_str(), e.what());
  }
}

TEST(Viewer, Maze_badsize_3) {
  try {
    Maze maze(10, 51);
  } catch (const std::invalid_argument& e) {
    std::string expected_error = "Error. The size exceeds the allowable.";
    ASSERT_STREQ(expected_error.c_str(), e.what());
  }
}

TEST(Viewer, Generation_maze) {
  Maze maze;
  maze.GenerationMaze(50, 50);
  size_t result_rows = 50;
  size_t result_cols = 50;
  Maze result_maze = Maze(result_rows, result_cols);
  ASSERT_EQ(maze.rows(), result_maze.rows());
  ASSERT_EQ(maze.cols(), result_maze.cols());
}

TEST(Viewer, FindPath) {
  Maze maze;
  std::string file_name = "../data-samples/maze4x4.mze";
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

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
