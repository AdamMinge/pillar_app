#ifndef PLUGIN_FLOW_FLOW_VIEW_H
#define PLUGIN_FLOW_FLOW_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsView>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FlowScene;

class FLOW_DOCUMENT_API FlowView : public QGraphicsView
{
  Q_OBJECT

public:
  explicit FlowView(QWidget *parent = nullptr);
  ~FlowView() override;

  void setScene(FlowScene *scene);
  [[nodiscard]] FlowScene *getScene() const;

public Q_SLOTS:
  void scaleUp();
  void scaleDown();

protected:
  void drawBackground(QPainter *painter, const QRectF &rect) override;
  void wheelEvent(QWheelEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void showEvent(QShowEvent *event) override;

private:
  QPointF m_mouse_click_pos;

  const QColor m_background_color;
  const QColor m_small_grid_color;
  const QColor m_grid_color;
};

#endif//PLUGIN_FLOW_FLOW_VIEW_H
