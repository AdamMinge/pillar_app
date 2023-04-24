#ifndef ABOUT_DIALOG_H
#define ABOUT_DIALOG_H

/* ----------------------------------- Utils -------------------------------- */
#include <utils/dialog/dialog_with_url_links.h>
/* -------------------------------------------------------------------------- */

namespace Ui {
class AboutDialog;
}

class AboutDialog : public utils::QtDialogWithUrlLinks<AboutDialog> {
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

#endif  // ABOUT_DIALOG_H
