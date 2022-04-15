#ifndef FLOW_FLOW_NODES_DOCK_H
#define FLOW_FLOW_NODES_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
/* -------------------------------------------------------------------------- */

class FlowNodesDock : public QDockWidget
{
  Q_OBJECT

public:
  explicit FlowNodesDock(QWidget *parent = nullptr);
  ~FlowNodesDock() override;

protected:
  void changeEvent(QEvent *event) override;

private:
  void initUi();
  void initConnections();

  void retranslateUi();
};

#endif//FLOW_FLOW_NODES_DOCK_H
