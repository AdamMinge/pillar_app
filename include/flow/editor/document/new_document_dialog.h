#ifndef FLOW_NEW_DOCUMENT_DIALOG_H
#define FLOW_NEW_DOCUMENT_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* -------------------------------------------------------------------------- */

namespace flow::document
{
  class NewDocumentWidget;
  class Document;
}// namespace flow::document

namespace Ui
{
  class NewDocumentDialog;
}

class DocumentTypeListModel;
class DocumentTypeListDelegate;

class NewDocumentDialog : public QDialog
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit NewDocumentDialog(QWidget *parent = nullptr);
  ~NewDocumentDialog() override;

  [[nodiscard]] std::unique_ptr<flow::document::Document> create();

protected:
  void changeEvent(QEvent *event) override;

private Q_SLOTS:
  void documentTypeChanged(const QModelIndex &index);
  void updateCreateButton();

private:
  void initUi();
  void initConnections();

  void retranslateUi();

  void writeSettings();
  void readSettings();

private:
  QScopedPointer<Ui::NewDocumentDialog> m_ui;

  QScopedPointer<Preferences> m_preferences;
  QScopedPointer<DocumentTypeListModel> m_document_types_model;
  QScopedPointer<DocumentTypeListDelegate> m_document_types_delegate;

  std::map<QString, flow::document::NewDocumentWidget *>
    m_document_create_widgets;
};

#endif//FLOW_NEW_DOCUMENT_DIALOG_H
