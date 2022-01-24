#ifndef FLOW_NEW_PROJECT_DIALOG_H
#define FLOW_NEW_PROJECT_DIALOG_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class NewProjectDialog;
}

namespace api
{
  class IProject;
}

class NewProjectDialog : public QDialog
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit NewProjectDialog(QWidget *parent = nullptr);
  ~NewProjectDialog() override;

  [[nodiscard]] std::unique_ptr<api::IProject> create();

protected:
  void changeEvent(QEvent *event) override;

private:
  void retranslateUi();

  void writeSettings();
  void readSettings();

private:
  QScopedPointer<Ui::NewProjectDialog> m_ui;
  QScopedPointer<Preferences> m_preferences;
};

#endif//FLOW_NEW_PROJECT_DIALOG_H
