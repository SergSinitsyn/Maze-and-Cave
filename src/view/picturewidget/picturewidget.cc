#include "picturewidget.h"

#include <QPoint>

#include "../../other/cell.h"

void PictureWidget::set_rows(size_t rows) {
  rows_ = rows;
  cell_size_.setHeight(size_ / rows_);
}
void PictureWidget::set_cols(size_t cols) {
  cols_ = cols;
  cell_size_.setWidth(size_ / cols_);
}

void PictureWidget::paintEvent(QPaintEvent* event) {
  painter_.begin(this);
  PaintPicture();
  painter_.end();
}

void PictureWidget::PaintPicture() {}

void PictureWidget::CheckTheme() {
  if (palette_ == QGuiApplication::palette()) {
    return;
  }
  palette_ = QGuiApplication::palette();
  SetTheme();
}

void PictureWidget::SetTheme() {
  if (palette_.color(QPalette::Window).lightness() < 128) {
    DarkTheme();
  } else {
    LightTheme();
  }
}

void PictureWidget::DarkTheme() {}

void PictureWidget::LightTheme() {}

QPoint PictureWidget::Center(const Cell& cell) {
  return QPoint((cell.col() + 0.5) * cell_size_.width(),
                (cell.row() + 0.5) * cell_size_.height());
}

QPoint PictureWidget::LeftTopCorner(const Cell& cell) {
  return QPoint(cell.col() * cell_size_.width(),
                cell.row() * cell_size_.height());
}

QPoint PictureWidget::LeftBottomCorner(const Cell& cell) {
  return QPoint(cell.col() * cell_size_.width(),
                (cell.row() + 1) * cell_size_.height());
}

QPoint PictureWidget::RightTopCorner(const Cell& cell) {
  return QPoint((cell.col() + 1) * cell_size_.width(),
                cell.row() * cell_size_.height());
}

QPoint PictureWidget::RightBottomCorner(const Cell& cell) {
  return QPoint((cell.col() + 1) * cell_size_.width(),
                (cell.row() + 1) * cell_size_.height());
}
