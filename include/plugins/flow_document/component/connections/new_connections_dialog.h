#ifndef FLOW_DOCUMENT_NEW_CONNECTIONS_DIALOG_H
#define FLOW_DOCUMENT_NEW_CONNECTIONS_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class NewConnectionsDialog;
}

namespace flow_document {

class FlowDocument;

class FLOW_DOCUMENT_API NewConnectionsDialog : public QDialog {
  Q_OBJECT

 public:
  NewConnectionsDialog(FlowDocument *document, QWidget *parent = nullptr);
  ~NewConnectionsDialog() override;

 public Q_SLOTS:
  void accept() override;

 protected Q_SLOTS:
  void changeEvent(QEvent *event) override;

  void fillLayers();

  void fillInputNodes();
  void fillOutputNodes();

  void fillInputPins();
  void fillOutputPins();

  void validate();

 private:
  void initUi();
  void initConnections();
  void retranslateUi();

 private:
  QScopedPointer<Ui::NewConnectionsDialog> m_ui;

  FlowDocument *m_document;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NEW_CONNECTIONS_DIALOG_H
