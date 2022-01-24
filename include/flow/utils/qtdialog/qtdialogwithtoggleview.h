#ifndef FLOW_TOOLS_DIALOG_WITH_TOGGLE_VIEW_H
#define FLOW_TOOLS_DIALOG_WITH_TOGGLE_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDialog>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qtdialog/export.h"
/* -------------------------------------------------------------------------- */

namespace utils
{

  class QTDIALOG_API QtDialogWithToggleView : public QDialog
  {
    Q_OBJECT

  public:
    explicit QtDialogWithToggleView(QWidget *parent = nullptr);
    ~QtDialogWithToggleView() override;

    [[nodiscard]] QAction *toggleViewAction() const;

  protected:
    void closeEvent(QCloseEvent *event) override;

  private Q_SLOTS:
    void titleChanged(const QString &title);

  private:
    QAction *m_toggle_view;
  };

}// namespace utils


#endif//FLOW_TOOLS_DIALOG_WITH_TOGGLE_VIEW_H
