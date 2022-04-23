#ifndef FLOW_NEW_PROJECT_DIALOG_H
#define FLOW_NEW_PROJECT_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class NewProjectDialog;
}

namespace flow::project
{
  class Project;
}

class NewProjectDialog : public QDialog
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit NewProjectDialog(QWidget *parent = nullptr);
  ~NewProjectDialog() override;

  [[nodiscard]] std::unique_ptr<flow::project::Project> create();

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

#endif//FLOW_NEW_PROJECT_DIALOG_H
