#ifndef MAZE_MODEL_MODEL_H
#define MAZE_MODEL_MODEL_H
#include <stdexcept>
#include <string>
#include <tuple>

class Model {
 public:
  static const size_t kMinCol = 2;
  static const size_t kMinRow = 2;
  static const size_t kMaxCol = 50;
  static const size_t kMaxRow = 50;
  Model(){};
  Model(size_t rows, size_t cols) : rows_(rows), cols_(cols){};
  virtual ~Model(){};
  std::pair<size_t, size_t> ReadSize(const std::string& filename);
  void ReadFile(const std::string& filename);

 protected:
  virtual void ReadLine(size_t& line_number, const std::string& line) {
    throw std::runtime_error("Not Implemented");
  };
  virtual void SetSize(std::pair<size_t, size_t> size) {
    std::tie(rows_, cols_) = size;
    lines_to_read_ = rows_ * 2;
  };
  size_t rows_ = 0;
  size_t cols_ = 0;
  size_t lines_to_read_ = 0;
};

#endif  // MAZE_MODEL_MODEL_H