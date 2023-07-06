#include "mazewidget.h"

#include <QPainter>
#include <QPoint>

#include "../../other/cell.h"
#include "../../other/mazecell.h"

void MazeWidget::set_enable_path(bool enable) {
  enable_path_ = enable;
  if (enable) {
    emit UpdateStartAndEndCell(start_cell_, end_cell_);
  } else {
    path_.clear();
    path_points_.clear();
  }
  update();
}

void MazeWidget::LoadMaze(MazeMatrix& maze) {
  path_.clear();
  set_rows(maze.row());
  set_cols(maze.col());
  maze_.clear();
  for (size_t row = 0; row < rows_; ++row) {
    for (size_t col = 0; col < cols_; ++col) {
      maze_.push_back(MazeCell(row, col, maze(row, col).right_wall(),
                               maze(row, col).bottom_wall()));
    }
  }
  DefaultStartAndEnd();
  update();
}

void MazeWidget::SetPath(std::vector<Cell> path) {
  path_ = path;
  path_points_.clear();
  std::transform(path_.begin(), path_.end(), std::back_inserter(path_points_),
                 [this](const auto& cell) { return Center(cell); });
}

void MazeWidget::paintEvent(QPaintEvent* event) {
  //  TODO сделать паттерн стратегия
  painter_.begin(this);
  PaintMaze();
  painter_.end();
}

void MazeWidget::mousePressEvent(QMouseEvent* event) {
  UpdateStartAndEnd(event);
}

void MazeWidget::mouseMoveEvent(QMouseEvent* event) {
  UpdateStartAndEnd(event);
}

void MazeWidget::CheckTheme() {
  if (palette_ == QGuiApplication::palette()) {
    return;
  }
  palette_ = QGuiApplication::palette();
  if (palette_.color(QPalette::Window).lightness() < 128) {
    wall_line_.setColor(Qt::white);
  } else {
    wall_line_.setColor(Qt::black);
  }
}

void MazeWidget::PaintMaze() {
  if (maze_.empty()) return;
  CheckTheme();
  PaintFrame();
  PaintWalls();
  if (enable_path_) {
    PaintPath();
    PaintStartAndEnd();
  }
}

void MazeWidget::PaintFrame() {
  painter_.setPen(wall_line_);
  painter_.drawRect(1, 1, size_ - 2, size_ - 2);
}

void MazeWidget::PaintWalls() {
  for (int i = 0; i < maze_.size(); ++i) {
    PaintMazeCell(maze_.at(i));
  }
}

void MazeWidget::PaintMazeCell(MazeCell& cell) {
  painter_.setPen(wall_line_);
  if (cell.bottom_wall())
    painter_.drawLine(LeftBottomCorner(cell), RightBottomCorner(cell));
  if (cell.right_wall())
    painter_.drawLine(RightTopCorner(cell), RightBottomCorner(cell));
}

void MazeWidget::PaintPath() {
  painter_.setPen(path_line_);
  painter_.drawPolyline(path_points_.data(), path_points_.size());
}

void MazeWidget::PaintStartAndEnd() {
  painter_.setPen(start_dot_);
  painter_.drawPoint(Center(start_cell_));
  painter_.setPen(end_dot_);
  painter_.drawPoint(Center(end_cell_));
}

void MazeWidget::DefaultStartAndEnd() {
  start_cell_ = Cell(0, 0);
  end_cell_ = Cell(rows_ - 1, cols_ - 1);
  if (!enable_path_) return;
  update();
  emit UpdateStartAndEndCell(start_cell_, end_cell_);
}

void MazeWidget::UpdateStartAndEnd(QMouseEvent* event) {
  if (!enable_path_) return;
  if (maze_.empty()) return;

  QPoint point = event->pos();
  int row = point.y() / cell_size_.height();
  int col = point.x() / cell_size_.width();
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) return;
  if (event->buttons() & Qt::LeftButton) {
    if (end_cell_ != Cell(row, col)) {
      end_cell_ = Cell(row, col);
      update();
      emit UpdateStartAndEndCell(start_cell_, end_cell_);
    }
  }
  if (event->buttons() & Qt::RightButton) {
    if (start_cell_ != Cell(row, col)) {
      start_cell_ = Cell(row, col);
      update();
      emit UpdateStartAndEndCell(start_cell_, end_cell_);
    }
  }
}
