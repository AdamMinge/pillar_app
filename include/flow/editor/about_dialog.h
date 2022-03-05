#ifndef FLOW_ABOUT_DIALOG_H
#define FLOW_ABOUT_DIALOG_H

/* ----------------------------------- Utils -------------------------------- */
#include <flow/utils/qt/dialog/dialog_with_url_links.h>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class AboutDialog;
}

class AboutDialog : public utils::QtDialogWithUrlLinks<AboutDialog>
{
  Q_OBJECT

public:
  explicit AboutDialog(QWidget *parent = nullptr);
  ~AboutDialog() override;

protected:
  void changeEvent(QEvent *event) override;

private:
  void retranslateUi();

private:
  QScopedPointer<Ui::AboutDialog> m_ui;
};

#endif//FLOW_ABOUT_DIALOG_H
