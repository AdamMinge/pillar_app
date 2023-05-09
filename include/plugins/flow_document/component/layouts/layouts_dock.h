#ifndef FLOW_DOCUMENT_LAYOUTS_DOCK_H
#define FLOW_DOCUMENT_LAYOUTS_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class LayoutsDock;
}

namespace flow_document {

class FLOW_DOCUMENT_API LayoutsDock : public QDockWidget {
  Q_OBJECT

 public:
  explicit LayoutsDock(QWidget *parent = nullptr);
  ~LayoutsDock() override;

 protected:
  void changeEvent(QEvent *event) override;

 private:
  void initUi();
  void initConnections();

  void retranslateUi();

 private:
  QScopedPointer<Ui::LayoutsDock> m_ui;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYOUTS_DOCK_H
