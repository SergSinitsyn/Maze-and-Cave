#include "controller.h"

#include "../model/cave/cave.h"
#include "../model/maze/maze.h"
#include "../view/mainwindow/mainwindow.h"

void Controller::SetModelMaze(Maze &model_maze) { model_maze_ = &model_maze; }

void Controller::SetModelCave(Cave &model_cave) { model_cave_ = &model_cave; }

void Controller::SetView(MainWindow &view) {
  view_ = &view;
  view_->SetController(*this);
  connect(view_, &MainWindow::generateCaveRequested, this, &Controller::GenerateCave);
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
  view_->SetPath(model_maze_->FindPath(start_cell, end_cell));
}

void Controller::LoadCaveFile(const std::string &file_name) {
  model_cave_->ReadFile(file_name);
  view_->LoadCaveFromModel(model_cave_->GetMatrix());
}

void Controller::GenerateCave(int rows, int cols, int chance) {
  model_cave_->Generate(rows, cols, chance);
  view_->LoadCaveFromModel(model_cave_->GetMatrix());
}

void Controller::CaveNextStep(int birth, int death) {
  model_cave_->MakeOneTurn(birth, death);
  view_->LoadCaveFromModel(model_cave_->GetMatrix());
}
