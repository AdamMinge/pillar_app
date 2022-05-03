#ifndef PLUGIN_FLOW_FLOW_TYPE_CONVERTERS_DOCK_H
#define PLUGIN_FLOW_FLOW_TYPE_CONVERTERS_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class FlowConvertersDock;
}

class FlowTypeConvertersTreeModel;
class FlowTypeConvertersTreeDelegate;

class FLOW_DOCUMENT_API FlowConvertersDock : public QDockWidget
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

  QScopedPointer<FlowTypeConvertersTreeModel> m_type_converters_model;
  QScopedPointer<QSortFilterProxyModel> m_converters_filter_model;
  QScopedPointer<FlowTypeConvertersTreeDelegate> m_type_converters_delegate;
};

#endif//PLUGIN_FLOW_FLOW_TYPE_CONVERTERS_DOCK_H
