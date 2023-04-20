#ifndef UTILS_WIDGET_SHORTCUT_SELECTOR_H
#define UTILS_WIDGET_SHORTCUT_SELECTOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLineEdit>
/* ----------------------------------- Local -------------------------------- */
#include "utils/widget/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

class WIDGET_API ShortcutSelector : public QLineEdit {
  Q_OBJECT

 public:
  explicit ShortcutSelector(QWidget *parent = nullptr);
  ~ShortcutSelector() override;

 protected:
  void keyPressEvent(QKeyEvent *event) override;
};

}  // namespace utils

#endif  // UTILS_WIDGET_SHORTCUT_SELECTOR_H
