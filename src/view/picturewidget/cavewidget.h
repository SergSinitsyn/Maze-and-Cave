#ifndef MAZE_VIEW_CAVEWIDGET_CAVEWIDGET_H_
#define MAZE_VIEW_CAVEWIDGET_CAVEWIDGET_H_

#include <QColor>
#include <QPainter>
#include <QtWidgets>
#include <vector>

#include "../../other/cavecell.h"
#include "../../other/cell.h"
#include "../../other/maze_matrix.h" // TODO заменить на cavematrix
#include "picturewidget.h"

class CaveWidget : public PictureWidget {
  Q_OBJECT
 public:
  CaveWidget(QWidget* parent = nullptr)
      : PictureWidget(parent),
        // TODO to google-style constructor
        wall_line_(Qt::black),
        cave_color_(Qt::black),
        palette_(QGuiApplication::palette()) {
    wall_line_.setWidth(2);
  }

  void LoadCave(MazeMatrix& maze);  // TODO заменить на cavematrix

 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  void CheckTheme();
  void PaintCave();
  void PaintCaveCell(CaveCell& cell); 

  std::vector<MazeCell> cave_;

  QPen wall_line_;
  QColor cave_color_;
  QPalette palette_;
};

#endif  //  MAZE_VIEW_CAVEWIDGET_CAVEWIDGET_H_
