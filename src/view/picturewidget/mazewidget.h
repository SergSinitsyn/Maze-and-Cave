#ifndef MAZE_VIEW_PICTUREWIDGET_MAZEWIDGET_H_
#define MAZE_VIEW_PICTUREWIDGET_MAZEWIDGET_H_

#include <QColor>
#include <QPainter>
#include <QtWidgets>
#include <vector>

#include "../../other/cell.h"
#include "../../other/maze_matrix.h"
#include "../../other/mazecell.h"
#include "picturewidget.h"

class MazeWidget : public PictureWidget {
  Q_OBJECT
 public:
  MazeWidget(QWidget* parent = nullptr)
      : PictureWidget(parent),
        // TODO to google-style constructor
        enable_path_(false),
        end_cell_(0, 0),
        start_cell_(0, 0),
        path_line_(Qt::red),
        start_dot_(Qt::magenta),
        end_dot_(Qt::cyan),
        wall_line_(Qt::black),
        palette_(QGuiApplication::palette()) {
    wall_line_.setWidth(2);
    path_line_.setWidth(2);
    start_dot_.setWidth(4);
    end_dot_.setWidth(4);
  }

  void set_enable_path(bool enable);
  void LoadMaze(MazeMatrix& maze);
  void SetPath(std::vector<Cell> path);

 signals:
  void UpdateStartAndEndCell(Cell start_cell, Cell end_cell);

 protected:
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;

 private:
  void CheckTheme();
  void PaintMaze();
  void PaintFrame();
  void PaintWalls();
  void PaintMazeCell(MazeCell& cell);
  void PaintPath();
  void PaintStartAndEnd();
  void DefaultStartAndEnd();
  void UpdateStartAndEnd(QMouseEvent* event);

  bool enable_path_;

  Cell start_cell_;
  Cell end_cell_;
  std::vector<MazeCell> maze_;
  std::vector<Cell> path_;
  std::vector<QPoint> path_points_;

  QPen path_line_;
  QPen start_dot_;
  QPen end_dot_;
  QPen wall_line_;
  QPalette palette_;
};

#endif  //  MAZE_VIEW_PICTUREWIDGET_MAZEWIDGET_H_