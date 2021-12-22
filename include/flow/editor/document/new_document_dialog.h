#ifndef FLOW_NEW_DOCUMENT_DIALOG_H
#define FLOW_NEW_DOCUMENT_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/document.h"
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class NewDocumentDialog;
}
class DocumentTypeListModel;
class DocumentTypeListDelegate;
class NewDocumentWidget;

class NewDocumentDialog : public QDialog
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit NewDocumentDialog(QWidget *parent = nullptr);
  ~NewDocumentDialog() override;

  [[nodiscard]] std::unique_ptr<Document> create();

protected:
  void changeEvent(QEvent *event) override;

private Q_SLOTS:
  void documentTypeChanged(const QModelIndex &index);

private:
  void retranslateUi();

  void writeSettings();
  void readSettings();

private:
  QScopedPointer<Ui::NewDocumentDialog> m_ui;

  QScopedPointer<Preferences> m_preferences;
  QScopedPointer<DocumentTypeListModel> m_document_types_model;
  QScopedPointer<DocumentTypeListDelegate> m_document_types_delegate;

  std::map<Document::Type, NewDocumentWidget *> m_document_create_widgets;
};

#endif//FLOW_NEW_DOCUMENT_DIALOG_H
