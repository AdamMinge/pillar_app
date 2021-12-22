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
};

#endif//FLOW_FLOW_VIEW_H
