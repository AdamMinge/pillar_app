#ifndef FLOW_DOCUMENT_PROPERTIES_DOCK_H
#define FLOW_DOCUMENT_PROPERTIES_DOCK_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/dock_widget.h"
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class PropertiesDock;
}

namespace flow {

class FlowDocument;

class LIB_FLOW_DOCUMENT_API PropertiesDock : public FlowDockWidget {
  Q_OBJECT

 public:
  explicit PropertiesDock(QWidget *parent = nullptr);
  ~PropertiesDock() override;

 protected Q_SLOTS:
  void changeEvent(QEvent *event) override;
  void onDocumentChanged(FlowDocument *from, FlowDocument *to) override;

 private Q_SLOTS:
  void searchProperties(const QString &search);

 private:
  void initUi();
  void initConnections();

  void retranslateUi();

 private:
  QScopedPointer<Ui::PropertiesDock> m_ui;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_PROPERTIES_DOCK_H
