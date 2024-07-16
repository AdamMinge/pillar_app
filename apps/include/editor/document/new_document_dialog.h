#ifndef NEW_DOCUMENT_DIALOG_H
#define NEW_DOCUMENT_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* -------------------------------------------------------------------------- */

namespace pillar {
class Document;
}  // namespace pillar

namespace Ui {
class NewDocumentDialog;
}

class NewDocumentWidgetListModel;
class NewDocumentWidgetListDelegate;

class NewDocumentDialog : public QDialog {
  Q_OBJECT

 private:
  struct Preferences;

 public:
  explicit NewDocumentDialog(QWidget *parent = nullptr);
  ~NewDocumentDialog() override;

  [[nodiscard]] std::unique_ptr<pillar::Document> create();

 protected:
  void changeEvent(QEvent *event) override;

 private Q_SLOTS:
  void currentChanged();
  void isValidChanged(bool valid);

 private:
  void initUi();
  void initConnections();

  void retranslateUi();

  void writeSettings();
  void readSettings();

 private:
  QScopedPointer<Ui::NewDocumentDialog> m_ui;

  QScopedPointer<Preferences> m_preferences;
  QScopedPointer<NewDocumentWidgetListModel> m_new_document_widget_model;
  QScopedPointer<NewDocumentWidgetListDelegate> m_new_document_widget_delegate;
};

#endif  // NEW_DOCUMENT_DIALOG_H
