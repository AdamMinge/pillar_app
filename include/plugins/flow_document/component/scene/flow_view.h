#ifndef PLUGIN_FLOW_FLOW_VIEW_H
#define PLUGIN_FLOW_FLOW_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsView>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowScene;

class FLOW_DOCUMENT_API FlowView : public QGraphicsView {
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
  void showEvent(QShowEvent *event) override;

 private:
  const QColor m_background_color;
  const QColor m_small_grid_color;
  const QColor m_grid_color;
};

}  // namespace flow_document

#endif  // PLUGIN_FLOW_FLOW_VIEW_H
