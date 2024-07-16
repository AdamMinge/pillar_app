#ifndef FLOW_DOCUMENT_CONNECTIONS_DOCK_H
#define FLOW_DOCUMENT_CONNECTIONS_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/flow_dock_widget.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class ConnectionsDock;
}

namespace flow_document {

class FlowDocument;
class ConnectionsTreeModel;

class FLOW_DOCUMENT_API ConnectionsDock : public FlowDockWidget {
  Q_OBJECT

 public:
  explicit ConnectionsDock(QWidget *parent = nullptr);
  ~ConnectionsDock() override;

 protected Q_SLOTS:
  void changeEvent(QEvent *event) override;
  void onDocumentChanged(FlowDocument *from, FlowDocument *to) override;

 private Q_SLOTS:
  void searchConnections(const QString &search);

 private:
  void initUi();
  void initConnections();

  void retranslateUi();

 private:
  QScopedPointer<Ui::ConnectionsDock> m_ui;

  QScopedPointer<ConnectionsTreeModel> m_connections_model;
  QScopedPointer<QSortFilterProxyModel> m_filter_model;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CONNECTIONS_DOCK_H
