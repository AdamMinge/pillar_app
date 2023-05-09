#ifndef FLOW_DOCUMENT_PROPERTIES_DOCK_H
#define FLOW_DOCUMENT_PROPERTIES_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class PropertiesDock;
}

namespace flow_document {

class FLOW_DOCUMENT_API PropertiesDock : public QDockWidget {
  Q_OBJECT

 public:
  explicit PropertiesDock(QWidget *parent = nullptr);
  ~PropertiesDock() override;

 protected:
  void changeEvent(QEvent *event) override;

 private:
  void initUi();
  void initConnections();

  void retranslateUi();

 private:
  QScopedPointer<Ui::PropertiesDock> m_ui;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_PROPERTIES_DOCK_H
