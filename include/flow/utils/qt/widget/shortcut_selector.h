#ifndef FLOW_SHORTCUT_SELECTOR_H
#define FLOW_SHORTCUT_SELECTOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLineEdit>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qt/widget/export.h"
/* -------------------------------------------------------------------------- */

namespace utils
{

  class WIDGET_API ShortcutSelector : public QLineEdit
  {
    Q_OBJECT

  public:
    explicit ShortcutSelector(QWidget *parent = nullptr);
    ~ShortcutSelector() override;

  protected:
    void keyPressEvent(QKeyEvent *event) override;
  };

}// namespace utils

#endif//FLOW_SHORTCUT_SELECTOR_H
