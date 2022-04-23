#ifndef PLUGIN_FLOW_FLOW_NODES_DOCK_H
#define PLUGIN_FLOW_FLOW_NODES_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QSortFilterProxyModel>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class FlowNodesDock;
}

class FlowNodesTreeModel;

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

private:
  QScopedPointer<Ui::FlowNodesDock> m_ui;

  QScopedPointer<FlowNodesTreeModel> m_nodes_model;
  QScopedPointer<QSortFilterProxyModel> m_nodes_filter_model;
};

#endif//PLUGIN_FLOW_FLOW_NODES_DOCK_H
