#ifndef MAZE_VIEW_PICTUREWIDGET_CAVEWIDGET_H_
#define MAZE_VIEW_PICTUREWIDGET_CAVEWIDGET_H_

#include <QColor>
#include <QPainter>
#include <QtWidgets>
#include <vector>

#include "../../other/cave_matrix.h"
#include "../../other/cavecell.h"
#include "../../other/cell.h"
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

  void LoadCave(const CaveMatrix& caze);

 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  void CheckTheme();
  void PaintCave();
  void PaintCaveCell(const CaveCell& cell);

  CaveMatrix cave_;
  QPen wall_line_;
  QColor cave_color_;
  QPalette palette_;
};

#endif  //  MAZE_VIEW_PICTUREWIDGET_CAVEWIDGET_H_
