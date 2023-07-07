#ifndef MAZE_VIEW_MAINWINDOW_MAINWINDOW_H_
#define MAZE_VIEW_MAINWINDOW_MAINWINDOW_H_

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
  void on_pushButton_load_maze_file_clicked();
  void on_pushButton_generate_clicked();
  void on_pushButton_save_maze_clicked();
  void on_pushButton_path_clicked(bool checked);
  void NewStartAndEndCell(Cell start_cell, Cell end_cell);

  // cave
  void on_pushButton_load_cave_file_clicked();
  void on_pushButton_next_step_clicked();
  void on_pushButton_automatic_work_clicked(bool checked);
  void BlockControls(bool status);
  void UnblockControlsAfterCaveLoad();

 private:
  Ui::MainWindow *ui_;
  Controller *controller_;
  QTimer *timer_ = new QTimer(this);
};
#endif  // MAZE_VIEW_MAINWINDOW_MAINWINDOW_H_
