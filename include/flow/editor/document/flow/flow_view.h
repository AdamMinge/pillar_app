#ifndef FLOW_FLOW_VIEW_H
#define FLOW_FLOW_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QGraphicsView>
/* -------------------------------------------------------------------------- */

class FlowScene;

class FlowView : public QGraphicsView
{
  Q_OBJECT

public:
  explicit FlowView(QWidget *parent = nullptr);
  ~FlowView() override;

  void setScene(FlowScene *scene);
  [[nodiscard]] FlowScene *getScene() const;

protected:
  void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
  const QColor m_background_color;
  const QColor m_small_grid_color;
  const QColor m_grid_color;
};

#endif//FLOW_FLOW_VIEW_H
