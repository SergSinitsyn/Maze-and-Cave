#include "cavewidget.h"

#include <QPainter>
#include <QPoint>
#include <QColor>

#include "../../other/cavecell.h"
#include "../../other/cell.h"

void CaveWidget::LoadCave(const CaveMatrix& cave) {
  cave_load_ = true;
  set_cols(cave.size());
  set_rows(cave.at(0).size());
  cave_ = &cave;
  update();
}

void CaveWidget::DarkTheme() { cave_color_ = Qt::white; }

void CaveWidget::LightTheme() { cave_color_ = Qt::black; }

void CaveWidget::PaintPicture() { PaintCave(); }

void CaveWidget::PaintCave() {
  if (!cave_load_) return;
  if (cave_->empty()) return;
  for (auto& row : *cave_)
    for (auto& cell : row) PaintCaveCell(cell);
}

void CaveWidget::PaintCaveCell(const CaveCell& cell) {
  if (cell.life()) {
    painter_.fillRect(QRect(LeftTopCorner(cell),
                            QSize(cell_size_.width(), cell_size_.height())),
                      cave_color_);
  }
}
