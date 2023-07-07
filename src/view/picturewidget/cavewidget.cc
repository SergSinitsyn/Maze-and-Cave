#include "cavewidget.h"

#include <QPainter>
#include <QPoint>

#include "../../other/cavecell.h"
#include "../../other/cell.h"

void CaveWidget::LoadCave(MazeMatrix& cave) {
  //! виджет для пещер еще в разработке
  //  set_rows(cave.rows());  // определить сколько строк и столбцов
  //  set_cols(cave.cols());

  // хранить ссылку на матрицу
  // cave_ = cave;
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
  if (cave_.empty()) return;
  // правильно ли?

  //  std::vector<std::vector<CaveCell>> cave;

  //  for (int i = 0; i < cave_.size(); ++i) {
  //    for (int j = 0; i < cave_.at(0).size(); ++j) {
  //      PaintCaveCell(cave_[i][j]);
  //    }
  //  }

  // правильно ли?
}

void CaveWidget::PaintCaveCell(CaveCell& cell) {
  painter_.setPen(wall_line_);
  if (cell.life())
    painter_.fillRect(QRect(LeftTopCorner(cell),
                            QSize(cell_size_.width(), cell_size_.height())),
                      Qt::white);
}
