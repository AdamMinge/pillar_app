#ifndef FLOW_DOCUMENT_FLOW_VIEW_H
#define FLOW_DOCUMENT_FLOW_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsView>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class FlowScene;

class LIB_FLOW_DOCUMENT_API FlowView : public QGraphicsView {
  Q_OBJECT

 public:
  struct ScaleRange {
    double minimum = 0;
    double maximum = 0;
  };

 public:
  explicit FlowView(QWidget *parent = nullptr);
  ~FlowView() override;

  void setScene(FlowScene *scene);
  [[nodiscard]] FlowScene *getScene() const;

  void setScaleRange(double minimum, double maximum);
  [[nodiscard]] ScaleRange getScaleRange() const;

 public Q_SLOTS:
  void scaleUp();
  void scaleDown();
  void setupScale(double scale);

 protected:
  void drawBackground(QPainter *painter, const QRectF &rect) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void showEvent(QShowEvent *event) override;
  void enterEvent(QEnterEvent *event) override;

 private:
  const QColor m_background_color;
  const QColor m_small_grid_color;
  const QColor m_grid_color;

  ScaleRange m_scale_range;
  QPointF m_mouse_clicked_pos;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_FLOW_VIEW_H
