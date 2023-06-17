#ifndef FLOW_DOCUMENT_PROPERTIES_DOCK_H
#define FLOW_DOCUMENT_PROPERTIES_DOCK_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/flow_dock_widget.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class PropertiesDock;
}

namespace flow_document {

class FlowDocument;

class FLOW_DOCUMENT_API PropertiesDock : public FlowDockWidget {
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

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_PROPERTIES_DOCK_H
