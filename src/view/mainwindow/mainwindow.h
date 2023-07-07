#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "../../other/maze_matrix.h"
#include "../../other/cave_matrix.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Controller;
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void SetController(Controller &controller);

  void LoadMazeFromModel(MazeMatrix &maze);
  void SetPath(std::vector<Cell> path);

  void LoadCaveFromModel(const CaveMatrix &cave);
  void NextStepCave();

 private slots:
  void on_tabWidget_controls_currentChanged(int index);
  // maze
  void NewStartAndEndCell(Cell start_cell, Cell end_cell);
  void on_pushButton_load_maze_file_clicked();
  void on_pushButton_generate_clicked();
  void on_pushButton_save_maze_clicked();
  void on_pushButton_path_clicked(bool checked);

  // cave
  void on_pushButton_load_cave_file_clicked();
  void on_pushButton_next_step_clicked();
  void on_pushButton_automatic_work_clicked(bool checked);
  void BlockControls(bool status);

 private:
  Ui::MainWindow *ui;  // TODO to google style
  Controller *controller_;
  QTimer *timer_ = new QTimer(this);
};
#endif  // MAINWINDOW_H
