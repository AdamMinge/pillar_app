#ifndef NEW_PROJECT_DIALOG_H
#define NEW_PROJECT_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* -------------------------------------------------------------------------- */

namespace Ui {
class NewProjectDialog;
}

namespace egnite {
class Project;
}

class NewProjectDialog : public QDialog {
  Q_OBJECT

 private:
  struct Preferences;

 public:
  explicit NewProjectDialog(QWidget *parent = nullptr);
  ~NewProjectDialog() override;

  [[nodiscard]] std::unique_ptr<egnite::Project> create();

 protected:
  void changeEvent(QEvent *event) override;

 private Q_SLOTS:
  void updateCreateButton();

 private:
  void initUi();
  void initConnections();

  void retranslateUi();

  void writeSettings();
  void readSettings();

 private:
  static const QString template_error_message;

 private:
  QScopedPointer<Ui::NewProjectDialog> m_ui;
  QScopedPointer<Preferences> m_preferences;
};

#endif  // NEW_PROJECT_DIALOG_H
