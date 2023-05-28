#ifndef FLOW_DOCUMENT_PROPERTIES_DOCK_H
#define FLOW_DOCUMENT_PROPERTIES_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class PropertiesDock;
}

namespace flow_document {

class FlowDocument;

class FLOW_DOCUMENT_API PropertiesDock : public QDockWidget {
  Q_OBJECT

 public:
  explicit PropertiesDock(QWidget *parent = nullptr);
  ~PropertiesDock() override;

  void setDocument(FlowDocument *document);
  [[nodiscard]] FlowDocument *getDocument() const;

 protected:
  void changeEvent(QEvent *event) override;

 private Q_SLOTS:
  void searchProperties(const QString &search);

 private:
  void initUi();
  void initConnections();

  void retranslateUi();

 private:
  FlowDocument *m_document;

  QScopedPointer<Ui::PropertiesDock> m_ui;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_PROPERTIES_DOCK_H
