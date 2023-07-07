#include "mainwindow.h"

#include "../../controller/controller.h"
#include "../picturewidget/cavewidget.h"
#include "../picturewidget/mazewidget.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  adjustSize();
  connect(ui_->maze_widget, &MazeWidget::UpdateStartAndEndCell, this,
          &MainWindow::NewStartAndEndCell);
  connect(timer_, &QTimer::timeout, this, &MainWindow::NextStepCave);
  ui_->tabWidget_controls->setCurrentIndex(0);
  ui_->stackedWidget_picture->setCurrentIndex(0);
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::SetController(Controller &controller) {
  controller_ = &controller;
}

void MainWindow::LoadMazeFromModel(MazeMatrix &maze) {
  ui_->maze_widget->LoadMaze(maze);
}

void MainWindow::SetPath(std::vector<Cell> path) {
  ui_->maze_widget->SetPath(path);
}

void MainWindow::LoadCaveFromModel(const CaveMatrix &cave) {
  ui_->cave_widget->LoadCave(cave);
}

void MainWindow::NextStepCave() {
  // TODO хранить приватные поля для значений? для повышения скорости?
  controller_->CaveNextStep(ui_->spinBox_birth_limit->value(),
                            ui_->spinBox_death_limit->value());
}

void MainWindow::on_tabWidget_controls_currentChanged(int index) {
  ui_->stackedWidget_picture->setCurrentIndex(index);
  ui_->statusbar->clearMessage();
}

void MainWindow::on_pushButton_load_maze_file_clicked() {
  ui_->statusbar->showMessage("Loading file...");
  QDir::currentPath();
  QString new_filename = QFileDialog::getOpenFileName(0, "Open", "", "*.mze");
  if (new_filename.isEmpty()) {
    ui_->statusbar->showMessage("File not selected");
    return;
  }
  try {
    controller_->LoadMazeFile(
        new_filename.toStdString());  // ! сделать в виде сигнала в контроллер?
    ui_->statusbar->showMessage("Correct load");
  } catch (const std::exception &exc) {
    QMessageBox::critical(this, "Warning", exc.what());
    ui_->statusbar->showMessage("Error loading file: '" + new_filename + "'" +
                                ", error:" + exc.what());
  }
}

void MainWindow::on_pushButton_generate_clicked() {
  controller_->GenerateMaze(
      ui_->spinBox_rows->value(),  // ! сделать в виде сигнала в контроллер?
      ui_->spinBox_cols->value());
}

void MainWindow::on_pushButton_save_maze_clicked() {
  QDir::currentPath();
  QString new_filename = QFileDialog::getSaveFileName(0, "Save", "", "*.mze");

  if (new_filename.isEmpty()) {
    ui_->statusbar->showMessage("Filename not selected");
    return;
  }

  controller_->SaveMazeToFile(new_filename.toStdString());
  //! а если память кончилась?
}

void MainWindow::on_pushButton_path_clicked(bool checked) {
  ui_->pushButton_path->setText(checked ? "Path Enable" : "Path Disable");
  ui_->maze_widget->set_enable_path(checked);
}

void MainWindow::NewStartAndEndCell(Cell start_cell, Cell end_cell) {
  controller_->FindPath(start_cell, end_cell);
  ui_->statusbar->showMessage(
      "Start cell is " + QString::number(start_cell.row() + 1) + "," +
      QString::number(start_cell.col() + 1) + "    ###    " + "End cell is " +
      QString::number(end_cell.row() + 1) + "," +
      QString::number(end_cell.col() + 1));
}

void MainWindow::on_pushButton_load_cave_file_clicked() {
  // TODO убрать дублирование кода
  ui_->statusbar->showMessage("Loading file...");
  QDir::currentPath();
  QString new_filename = QFileDialog::getOpenFileName(0, "Open", "", "*.cve");
  if (new_filename.isEmpty()) {
    ui_->statusbar->showMessage("File not selected");
    return;
  }
  try {
    controller_->LoadCaveFile(
        new_filename.toStdString());  // ! сделать в виде сигнала в контроллер?
    ui_->statusbar->showMessage("Correct load");
    UnblockControlsAfterCaveLoad();  // !
  } catch (const std::exception &exc) {
    QMessageBox::critical(this, "Warning", exc.what());
    ui_->statusbar->showMessage("Error loading file: '" + new_filename + "'" +
                                ", error:" + exc.what());
  }
}

void MainWindow::on_pushButton_next_step_clicked() { NextStepCave(); }

void MainWindow::on_pushButton_automatic_work_clicked(bool checked) {
  if (checked) {
    BlockControls(!checked);
    timer_->start(ui_->spinBox_periodicity->value());
  } else {
    timer_->stop();
    BlockControls(!checked);
  }
}

void MainWindow::BlockControls(bool status) {
  ui_->pushButton_load_cave_file->setEnabled(status);
  ui_->pushButton_next_step->setEnabled(status);
  ui_->spinBox_birth_limit->setEnabled(status);
  ui_->spinBox_death_limit->setEnabled(status);
  ui_->spinBox_periodicity->setEnabled(status);
  ui_->tabWidget_controls->setTabEnabled(0, status);
}

void MainWindow::UnblockControlsAfterCaveLoad() {
  ui_->pushButton_next_step->setEnabled(true);
  ui_->spinBox_birth_limit->setEnabled(true);
  ui_->spinBox_death_limit->setEnabled(true);
  ui_->spinBox_periodicity->setEnabled(true);
  ui_->pushButton_automatic_work->setEnabled(true);
}
