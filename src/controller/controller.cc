#include "controller.h"

#include "../model/cave/cave.h"
#include "../model/maze/maze.h"
#include "../view/mainwindow/mainwindow.h"

void Controller::SetModelMaze(Maze &model_maze) { model_maze_ = &model_maze; }

void Controller::SetModelCave(Cave &model_cave) { model_cave_ = &model_cave; }

void Controller::SetView(MainWindow &view) {
  view_ = &view;
  view_->SetController(*this);
}

void Controller::LoadMazeFile(const std::string &file_name) {
  model_maze_->ReadFile(file_name);
  view_->LoadMazeFromModel(model_maze_->maze_matrix());
}

void Controller::GenerateMaze(int rows, int cols) {
  model_maze_->GenerationMaze(rows, cols);
  view_->LoadMazeFromModel(model_maze_->maze_matrix());
}

void Controller::SaveMazeToFile(const std::string &file_name) {
  model_maze_->WriteFile(file_name);
}

void Controller::FindPath(Cell start_cell, Cell end_cell) {
  // model_maze_->FindPath(start_row, start_col, end_row, end_col);
  // view_->SetPath(model_maze_->GetPath());

  view_->SetPath(model_maze_->FindPath(start_cell, end_cell));

  // ? если пути нет - вектор пустой
  // ? если начальная тогка совпадает с конечной - вектор пустой??? или не
  // давать ? такой сигнал в модель вообще
}

void Controller::LoadCaveFile(const std::string &file_name) {
  // model_cave_->ReadFile(file_name);

}

void Controller::CaveNextStep(int birth, int death) {
  //
}
