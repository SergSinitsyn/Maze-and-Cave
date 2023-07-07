
#include "../model/cave/cave.h"

#include <gtest/gtest.h>

TEST(Cave, ReadFile_File_empty) {
  Cave cave(5, 5);
  std::string file_name = "maze-samples/cave_empty.cve";
  try {
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

TEST(Cave, ReadFile) {
  Cave cave(5, 7);
  std::string file_name = "maze-samples/cave_1.cve";
  cave.ReadFile(file_name);
  size_t result_rows = 10;
  size_t result_cols = 10;
  Cave result_cave = Cave(result_rows, result_cols);
  ASSERT_EQ(cave.rows(), result_cave.rows());
  ASSERT_EQ(cave.cols(), result_cave.cols());

  CaveMatrix result_matrix = {
      {1, 0, 1, 0, 0, 0, 0, 1, 1, 0}, {0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
      {0, 0, 1, 0, 1, 0, 1, 1, 0, 1}, {0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
      {0, 0, 0, 1, 1, 0, 0, 1, 1, 1}, {0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
      {1, 1, 0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
      {1, 0, 0, 0, 0, 1, 1, 0, 0, 0}, {0, 1, 1, 0, 0, 1, 1, 0, 0, 0}};

  CaveMatrix file_matrix = cave.GetMatrix();
  for (size_t i = 0; i < result_rows; ++i) {
    for (size_t j = 0; j < result_cols; ++j) {
      ASSERT_EQ(file_matrix[i][j].life(), !result_matrix[i][j].life());
    }
  }
}

TEST(Cave, Generate) {
  const int kSize = 10;
  Cave cave(kSize, kSize);
  CaveMatrix matrix = cave.GetMatrix();
  for (size_t i = 0; i < kSize; ++i) {
    int sum = 0;
    int prev_sum = 0;
    for (size_t j = 0; j < kSize; ++j) {
      sum += matrix[i][j].life();
    }
    ASSERT_TRUE(sum > 0);
    ASSERT_TRUE(sum < kSize);
    ASSERT_TRUE(prev_sum != sum);
    prev_sum = sum;
    sum = 0;
  }
}