#include "model.h"

#include <fstream>
#include <tuple>

std::pair<size_t, size_t> Model::ReadSize(const std::string& line) {
  size_t pos = 0;
  size_t rows_number = std::stoi(&line.at(pos), &pos);
  size_t cols_number = std::stoi(&line.at(pos));
  if (rows_number <= Model::kMinRow || cols_number <= Model::kMinCol ||
      rows_number > Model::kMaxRow || cols_number > Model::kMaxCol) {
    throw std::invalid_argument(
        "File read error. The dimensions are not correct.");
  }
  return {rows_number, cols_number};
}

void Model::ReadFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file) {
    throw std::invalid_argument("File read error. The file is missing.");
  }
  if (file.peek() == std::ifstream::traits_type::eof()) {
    throw std::invalid_argument("File read error. The file is empty.");
  }
  std::string line;
  std::getline(file, line);
  SetSize(ReadSize(line));
  for (size_t i = 0; i < lines_to_read_; ++i) {
    std::getline(file, line);
    if (!line.empty()) {
      ReadLine(i, line);
    } else {
      --i;
    }
  }
  file.close();
}