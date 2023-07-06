#include <QApplication>

#include "controller/controller.h"
// #include "model/cave/cave.h"  
#include "model/maze/maze.h"
#include "view/mainwindow/mainwindow.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  MainWindow view;
  Maze model_maze_;
  // Cave model_cave_;
  Controller& controller = Controller::GetInstance();
  controller.SetModelMaze(model_maze_);
  // controller.SetModelCave(model_cave_);
  controller.SetView(view);
  view.show();
  return app.exec();
}

// разблокировать комментарии когда будут работать пещеры (или для их создания)
