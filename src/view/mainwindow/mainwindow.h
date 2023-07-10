#ifndef MAZE_VIEW_MAINWINDOW_MAINWINDOW_H_
#define MAZE_VIEW_MAINWINDOW_MAINWINDOW_H_

#include <QMainWindow>
#include <QTimer>

#include "../../other/cave_matrix.h"
#include "../../other/maze_matrix.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void LoadMazeFromModel(MazeMatrix &maze);
  void SetPath(std::vector<Cell> path);

  void LoadCaveFromModel(const CaveMatrix &cave);
  void NextStepCave();

 private slots:
  void on_tabWidget_controls_currentChanged(int index);

  // maze
  void on_pushButton_load_maze_file_clicked();
  void on_pushButton_generate_maze_clicked();
  void on_pushButton_save_maze_clicked();
  void on_pushButton_path_clicked(bool checked);
  void NewStartAndEndCell(Cell start_cell, Cell end_cell);
  void UnblockControlsAfterMazeLoad();

  // cave
  void on_pushButton_load_cave_file_clicked();
  void on_pushButton_generate_cave_clicked();
  void on_pushButton_next_step_clicked();
  void on_pushButton_automatic_work_clicked(bool checked);
  void BlockControls(bool status);
  void UnblockControlsAfterCaveLoad();

 private:
  Ui::MainWindow *ui_;
  QTimer *timer_ = new QTimer(this);

 signals:
  void LoadMazeFile(const std::string &file_name);
  void GenerateMaze(int rows, int cols);
  void SaveMazeToFile(const std::string &file_name);
  void FindPath(Cell start_cell, Cell end_cell);

  void LoadCaveFile(const std::string &file_name);
  void GenerateCave(int rows, int cols, int chance);
  void CaveNextStep(int birth, int death);
};
#endif  // MAZE_VIEW_MAINWINDOW_MAINWINDOW_H_
