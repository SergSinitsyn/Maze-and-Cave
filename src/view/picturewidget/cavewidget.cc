#include "cavewidget.h"

#include <QPainter>
#include <QPoint>

#include "../../other/cavecell.h"
#include "../../other/cell.h"

void CaveWidget::LoadCave(MazeMatrix& cave) {
  //! виджет для пещер еще в разработке

  // set_rows(cave.row());
  // set_cols(cave.col());
  // cave_.clear();
  // for (size_t row = 0; row < rows_; ++row) {
  //   for (size_t col = 0; col < cols_; ++col) {
  //     cave_.push_back(MazeCell(row, col, maze(row, col).life()));
  //   }
  // }
  // update();
}

void CaveWidget::CheckTheme() {
  if (palette_ == QGuiApplication::palette()) {
    return;
  }
  palette_ = QGuiApplication::palette();
  if (palette_.color(QPalette::Window).lightness() < 128) {
    wall_line_.setColor(Qt::white);
    // cave_color_.setColor(Qt::white);
  } else {
    wall_line_.setColor(Qt::black);
    // cave_color_.setColor(Qt::black);
  }
}

void CaveWidget::paintEvent(QPaintEvent* event) {
  painter_.begin(this);
  PaintCave();
  painter_.end();
}

void CaveWidget::PaintCave() {
  // for (int i = 0; i < cave_.size(); ++i) {
  //   PaintCaveCell(cave_.at(i));
  // }
}

void CaveWidget::PaintCaveCell(CaveCell& cell) {
  // painter_.setPen(wall_line_);
  // if (cell.life())
  //   painter_.fillRect(QRect(LeftTopCorner(cell),
  //                           QSize(cell_size_.width(), cell_size_.height())),
  //                     Qt::white);
}