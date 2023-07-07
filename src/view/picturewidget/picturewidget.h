#ifndef MAZE_VIEW_PICTUREWIDGET_PICTUREWIDGET_H_
#define MAZE_VIEW_PICTUREWIDGET_PICTUREWIDGET_H_

#include <QPainter>
#include <QtWidgets>

#include "../../other/cell.h"

class PictureWidget : public QWidget {
  Q_OBJECT
 public:
  explicit PictureWidget(QWidget* parent = nullptr)
      : QWidget(parent),
        // TODO to google-style constructor
        size_(500),
        rows_(10),
        cols_(10),
        cell_size_(size_ / cols_, size_ / rows_),
        palette_(QGuiApplication::palette()) {
    SetTheme();
  }

  void set_rows(size_t rows);
  void set_cols(size_t cols);

 protected:
  void paintEvent(QPaintEvent* event) override;
  virtual void PaintPicture();
  void CheckTheme();
  void SetTheme();
  virtual void DarkTheme();
  virtual void LightTheme();

  QPoint Center(const Cell& cell);
  QPoint LeftTopCorner(const Cell& cell);
  QPoint LeftBottomCorner(const Cell& cell);
  QPoint RightTopCorner(const Cell& cell);
  QPoint RightBottomCorner(const Cell& cell);

  const double size_;
  size_t rows_;
  size_t cols_;
  QSizeF cell_size_;
  QPainter painter_;
  QPalette palette_;
};

#endif  //  MAZE_VIEW_PICTUREWIDGET_PICTUREWIDGET_H_
