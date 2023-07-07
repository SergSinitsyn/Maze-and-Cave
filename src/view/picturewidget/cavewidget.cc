#include "cavewidget.h"

#include <QPainter>
#include <QPoint>
#include <vector>

#include "../../other/cavecell.h"
#include "../../other/cell.h"

void CaveWidget::LoadCave(const CaveMatrix& cave) {
  set_cols(cave.size());
  set_rows(cave.at(0).size());
  cave_ = cave;
  update();
}

void CaveWidget::CheckTheme() {
  if (palette_ == QGuiApplication::palette()) {
    return;
  }
  palette_ = QGuiApplication::palette();
  if (palette_.color(QPalette::Window).lightness() < 128) {
    wall_line_.setColor(Qt::white);
    // cave_color_.setColor(Qt::white);
    // TODO цвет по теме устройства
  } else {
    wall_line_.setColor(Qt::black);
    // cave_color_.setColor(Qt::black);
    // TODO цвет по теме устройства
  }
}

void CaveWidget::paintEvent(QPaintEvent* event) {
  painter_.begin(this);
  CheckTheme();
  PaintCave();
  painter_.end();
}

void CaveWidget::PaintCave() {
  if (cave_.empty()) return;
  for (int i = 0; i < cave_.size(); ++i) {
    for (int j = 0; i < cave_.at(0).size(); ++j) {
      PaintCaveCell(cave_[i][j]);
    }
  }
}

void CaveWidget::PaintCaveCell(const CaveCell& cell) {
  painter_.setPen(wall_line_);
  if (cell.life())
    painter_.fillRect(QRect(LeftTopCorner(cell),
                            QSize(cell_size_.width(), cell_size_.height())),
                      Qt::blue);
  // TODO цвет по теме устройства
}
