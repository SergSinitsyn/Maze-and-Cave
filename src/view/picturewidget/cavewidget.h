#ifndef MAZE_VIEW_PICTUREWIDGET_CAVEWIDGET_H_
#define MAZE_VIEW_PICTUREWIDGET_CAVEWIDGET_H_

#include <QColor>
#include <QPainter>
#include <QtWidgets>

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
        cave_color_(Qt::blue) {
    SetTheme();
  }

  void LoadCave(const CaveMatrix& caze);

 private:
  void PaintPicture() override;
  void DarkTheme() override;
  void LightTheme() override;
  void PaintCave();
  void PaintCaveCell(const CaveCell& cell);

  const CaveMatrix* cave_{nullptr};
  QColor cave_color_;
  bool cave_load_{false};
};

#endif  //  MAZE_VIEW_PICTUREWIDGET_CAVEWIDGET_H_
