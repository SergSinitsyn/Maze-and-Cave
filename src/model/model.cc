#include "model.h"

#include <fstream>
#include <tuple>

std::pair<size_t, size_t> Model::ReadSize(const std::string& line) {
  size_t pos = 0;
  size_t rows = std::stoi(&line.at(pos), &pos);
  size_t cols = std::stoi(&line.at(pos));
  if (rows <= Model::kMinRow || cols <= Model::kMinCol ||
      rows > Model::kMaxRow || cols > Model::kMaxCol) {
    throw std::invalid_argument(
        "File read error. The dimensions are not correct.");
  }
  return {rows, cols};
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