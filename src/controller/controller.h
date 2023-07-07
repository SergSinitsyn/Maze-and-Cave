#ifndef MAZE_CONTROLLER_CONTROLLER_H_
#define MAZE_CONTROLLER_CONTROLLER_H_

#include "../model/cave/cave.h"
#include "../model/maze/maze.h"
#include "../view/mainwindow/mainwindow.h"

#include "../other/cavecell.h" // !

template <typename T>
class Singleton {
 public:
  static T& GetInstance() {
    static T instance;
    return instance;
  }

 protected:
  Singleton() = default;
  virtual ~Singleton() = default;

 private:
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
};

using CaveMatrix = std::vector<std::vector<CaveCell>>;

class Controller : public Singleton<Controller> {
 public:
  friend class Singleton<Controller>;

  void SetModelMaze(Maze& model_maze);
  void SetModelCave(Cave& model_cave);
  void SetView(MainWindow& view);

  void LoadMazeFile(const std::string& file_name);
  void GenerateMaze(int rows, int cols);
  void SaveMazeToFile(const std::string &file_name);
  void FindPath (Cell start_cell, Cell end_cell);

  void LoadCaveFile(const std::string& file_name);
  void CaveNextStep(int birth, int death);

 private:
  Controller() = default;
  // Model* model_{nullptr}; // delete
  Maze* model_maze_{nullptr};
  Cave* model_cave_{nullptr};
  MainWindow* view_{nullptr};
};

#endif  // MAZE_CONTROLLER_CONTROLLER_H_
