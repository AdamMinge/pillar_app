#ifndef FLOW_FLOW_TYPE_CONVERTERS_DOCK_H
#define FLOW_FLOW_TYPE_CONVERTERS_DOCK_H

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

class FlowConvertersTreeModel;

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

  QScopedPointer<FlowConvertersTreeModel> m_converters_model;
  QScopedPointer<QSortFilterProxyModel> m_converters_filter_model;
};

#endif//FLOW_FLOW_TYPE_CONVERTERS_DOCK_H
