#include "mainwindow.h"

#include "../../controller/controller.h"
#include "../picturewidget/cavewidget.h"
#include "../picturewidget/mazewidget.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  adjustSize();
  connect(ui->maze_widget, &MazeWidget::UpdateStartAndEndCell, this,
          &MainWindow::NewStartAndEndCell);
  connect(timer, &QTimer::timeout, this, &MainWindow::NextStepCave);
  ui->tabWidget_controls->setCurrentIndex(0);
  ui->stackedWidget_picture->setCurrentIndex(0);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::SetController(Controller &controller) {
  controller_ = &controller;
}

void MainWindow::LoadMazeFromModel(MazeMatrix &maze) {
  ui->maze_widget->LoadMaze(maze);
}

void MainWindow::LoadCaveFromModel(MazeMatrix &cave) {
  // ui->maze_widget->LoadCave(cave);
}

void MainWindow::SetPath(std::vector<Cell> path) {
  ui->maze_widget->SetPath(path);
}

void MainWindow::NewStartAndEndCell(Cell start_cell, Cell end_cell) {
  controller_->FindPath(start_cell, end_cell);  // рефакторить?
  ui->statusbar->showMessage(
      "Start cell is " + QString::number(start_cell.row() + 1) + "," +
      QString::number(start_cell.col() + 1) + "    ###    " + "End cell is " +
      QString::number(end_cell.row() + 1) + "," +
      QString::number(end_cell.col() + 1));
}

void MainWindow::on_pushButton_load_maze_file_clicked() {
  ui->statusbar->showMessage("Loading file...");
  QDir::currentPath();
  QString new_filename = QFileDialog::getOpenFileName(0, "Open", "", "*.mze");
  if (new_filename.isEmpty()) {
    ui->statusbar->showMessage("File not selected");
    return;
  }
  try {
    controller_->LoadMazeFile(
        new_filename.toStdString());  // ! сделать в виде сигнала в контроллер?
    ui->statusbar->showMessage("Correct load");
  } catch (const std::exception &exc) {
    QMessageBox::critical(this, "Warning", exc.what());
    ui->statusbar->showMessage("Error loading file: '" + new_filename + "'" +
                               ", error:" + exc.what());
  }
}

void MainWindow::on_pushButton_generate_clicked() {
  controller_->GenerateMaze(
      ui->spinBox_rows->value(),  // ! сделать в виде сигнала в контроллер?
      ui->spinBox_cols->value());
}

void MainWindow::on_pushButton_save_maze_clicked() {
  QDir::currentPath();
  QString new_filename = QFileDialog::getSaveFileName(0, "Save", "", "*.mze");

  if (new_filename.isEmpty()) {
    ui->statusbar->showMessage("Filename not selected");
    return;
  }

  controller_->SaveMazeToFile(new_filename.toStdString());
  //! а если память кончилась?
}

void MainWindow::on_pushButton_load_cave_file_clicked() {
  //
}

void MainWindow::on_pushButton_next_step_clicked() { NextStepCave(); }

void MainWindow::on_tabWidget_controls_currentChanged(int index) {
  ui->stackedWidget_picture->setCurrentIndex(index);
  ui->statusbar->clearMessage();
}

void MainWindow::on_pushButton_path_clicked(bool checked) {
  ui->pushButton_path->setText(checked ? "Path Enable" : "Path Disable");
  ui->maze_widget->set_enable_path(checked);
}

void MainWindow::on_pushButton_automatic_work_clicked(bool checked) {
  if (checked) {
    BlockControls(!checked);
    timer->start(ui->spinBox_periodicity->value());
  } else {
    timer->stop();
    BlockControls(!checked);
  }
}

void MainWindow::BlockControls(bool status) {
  ui->pushButton_load_cave_file->setEnabled(status);
  ui->pushButton_next_step->setEnabled(status);
  ui->spinBox_birth_limit->setEnabled(status);
  ui->spinBox_death_limit->setEnabled(status);
  ui->spinBox_periodicity->setEnabled(status);
  ui->tabWidget_controls->setTabEnabled(0, status);
}

void MainWindow::NextStepCave() {
  // хранить приватные поля для значений? для повышения скорости
  controller_->CaveNextStep(ui->spinBox_birth_limit->value(),
                            ui->spinBox_death_limit->value());
}
