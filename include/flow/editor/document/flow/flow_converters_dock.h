#ifndef FLOW_FLOW_CONVERTERS_DOCK_H
#define FLOW_FLOW_CONVERTERS_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QSortFilterProxyModel>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class FlowConvertersDock;
}

class FlowConvertersTreeModel;

class FlowConvertersDock : public QDockWidget
{
  Q_OBJECT

public:
  explicit FlowConvertersDock(QWidget *parent = nullptr);
  ~FlowConvertersDock() override;

protected:
  void changeEvent(QEvent *event) override;

private:
  void initUi();
  void initConnections();

  void retranslateUi();

private:
  QScopedPointer<Ui::FlowConvertersDock> m_ui;

  QScopedPointer<FlowConvertersTreeModel> m_converters_model;
  QScopedPointer<QSortFilterProxyModel> m_converters_filter_model;
};

#endif//FLOW_FLOW_CONVERTERS_DOCK_H
