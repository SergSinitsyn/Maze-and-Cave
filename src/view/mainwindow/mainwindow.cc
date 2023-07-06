#include "mainwindow.h"

#include "../../controller/controller.h"
#include "./ui_mainwindow.h"
#include "../picturewidget/mazewidget.h"
#include "../picturewidget/cavewidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->widget, &MazeWidget::UpdateStartAndEndCell, this,
          &MainWindow::NewStartAndEndCell);
  adjustSize();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::SetController(Controller &controller) {
  controller_ = &controller;
}

void MainWindow::LoadMazeFromModel(MazeMatrix &maze) {
  maze_load_ = true;  //! не здесь?
  ui->widget->LoadMaze(maze);
}

void MainWindow::LoadCaveFromModel(MazeMatrix &cave) {
  // maze_load_ = true;  //! не здесь?
  // ui->widget->LoadCave(cave);
}

void MainWindow::SetPath(std::vector<Cell> path) {
  ui->widget->SetPath(path);
}

void MainWindow::NewStartAndEndCell(Cell start_cell , Cell end_cell) {
  controller_->FindPath( start_cell,  end_cell);  // рефакторить?
  ui->statusbar->showMessage(
      "Start cell is " + QString::number(start_cell.row() + 1) + "," +
      QString::number(start_cell.col() + 1) + "    ###    " + "End cell is " +
      QString::number(end_cell.row() + 1) + "," + QString::number(end_cell.col() + 1));
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

void MainWindow::on_pushButton_next_step_clicked() {
  //
  //    controller_->CaveNextStep();
}

void MainWindow::on_tabWidget_currentChanged(int index) {
  // ui->widget->set_mode(static_cast<MazeWidget::Mode>(index));
}

void MainWindow::on_pushButton_path_clicked(bool checked) {
  ui->pushButton_path->setText(checked ? "Path Enable" : "Path Disable");
  ui->widget->set_enable_path(checked);
}

void MainWindow::on_pushButton_automatic_work_clicked(bool checked) {
  // TODO block other vidgets (buttons)
  // ?период доступный изменения во ввремя работы автономного режима

  // скорость выбирается здесь же
  // поэтому сделать для этого метод

  // цикле запусткается
  //  controller_->CaveNextStep();
}
