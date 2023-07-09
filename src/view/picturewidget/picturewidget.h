#ifndef MAZE_VIEW_PICTUREWIDGET_PICTUREWIDGET_H_
#define MAZE_VIEW_PICTUREWIDGET_PICTUREWIDGET_H_

#include <QPainter>
#include <QtWidgets>

#include "../../other/cell.h"

class PictureWidget : public QWidget {
  Q_OBJECT
 public:
  explicit PictureWidget(QWidget* parent = nullptr) : QWidget(parent) {}
  void set_rows(size_t rows);
  void set_cols(size_t cols);

 protected:
  static constexpr double size_{500};
  
  void paintEvent(QPaintEvent* event) override;
  virtual void PaintPicture() = 0;
  void CheckTheme();
  void SetTheme();
  virtual void DarkTheme() = 0;
  virtual void LightTheme() = 0;

  QPointF Center(const Cell& cell);
  QPointF LeftTopCorner(const Cell& cell);
  QPointF LeftBottomCorner(const Cell& cell);
  QPointF RightTopCorner(const Cell& cell);
  QPointF RightBottomCorner(const Cell& cell);

  size_t rows_{25};
  size_t cols_{25};
  QSizeF cell_size_{size_ / cols_, size_ / rows_};
  QPainter painter_;
  QPalette palette_{QGuiApplication::palette()};
};

#endif  //  MAZE_VIEW_PICTUREWIDGET_PICTUREWIDGET_H_
