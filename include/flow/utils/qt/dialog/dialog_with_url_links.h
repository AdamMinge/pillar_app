#ifndef FLOW_DIALOG_WITH_URL_LINKS_H
#define FLOW_DIALOG_WITH_URL_LINKS_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
#include <QUrl>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qt/dialog/export.h"
/* -------------------------------------------------------------------------- */

namespace utils
{
  template<typename TYPE>
  class DIALOG_API QtDialogWithUrlLinks : public QDialog
  {
  public:
    static void show(const QUrl &url = QUrl{}, QWidget *parent = nullptr);
    static void exec(const QUrl &url = QUrl{}, QWidget *parent = nullptr);

    virtual void setUrl(const QUrl &url);

  protected:
    explicit QtDialogWithUrlLinks(QWidget *parent = nullptr);
    ~QtDialogWithUrlLinks() override;
  };

  template<typename TYPE>
  void QtDialogWithUrlLinks<TYPE>::show(const QUrl &url, QWidget *parent)
  {
    static QPointer<TYPE> dialog = nullptr;

    if (!dialog)
    {
      dialog = new TYPE(parent);
      dialog->setAttribute(Qt::WA_DeleteOnClose);
    }

    dialog->setUrl(url);
    dialog->show();
    dialog->activateWindow();
    dialog->raise();
  }

  template<typename TYPE>
  void QtDialogWithUrlLinks<TYPE>::exec(const QUrl &url, QWidget *parent)
  {
    static QPointer<TYPE> dialog = nullptr;

    if (!dialog) { dialog = new TYPE(parent); }

    dialog->setUrl(url);
    dialog->QDialog::exec();
  }

  template<typename TYPE>
  void QtDialogWithUrlLinks<TYPE>::setUrl(const QUrl &url)
  {}

  template<typename TYPE>
  QtDialogWithUrlLinks<TYPE>::QtDialogWithUrlLinks(QWidget *parent)
      : QDialog(parent)
  {}

  template<typename TYPE>
  QtDialogWithUrlLinks<TYPE>::~QtDialogWithUrlLinks() = default;

}// namespace utils

#endif//FLOW_DIALOG_WITH_URL_LINKS_H
