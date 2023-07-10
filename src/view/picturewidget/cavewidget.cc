#include "cavewidget.h"

#include <QColor>
#include <QPainter>
#include <QPoint>
#include <QRect>

#include "../../other/cavecell.h"
#include "../../other/cell.h"

void CaveWidget::LoadCave(const CaveMatrix& cave) {
  cave_load_ = true;
  set_rows(cave.size());
  set_cols(cave.at(0).size());
  cave_ = &cave;
  update();
}

void CaveWidget::DarkTheme() { cave_color_ = Qt::white; }

void CaveWidget::LightTheme() { cave_color_ = Qt::black; }

void CaveWidget::PaintPicture() {
  if (!cave_load_) return;
  if (cave_->empty()) return;
  for (const auto& row : *cave_)
    for (const auto& cell : row) PaintCaveCell(cell);
}

void CaveWidget::PaintCaveCell(const CaveCell& cell) {
  if (cell.life()) {
    painter_.fillRect(QRectF(LeftTopCorner(cell), cell_size_), cave_color_);
  }
}
