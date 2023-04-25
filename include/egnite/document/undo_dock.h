#ifndef EGNITE_UNDO_DOCK_H
#define EGNITE_UNDO_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QUndoStack>
#include <QUndoView>
/* ----------------------------------- Local -------------------------------- */
#include "egnite/export.h"
/* -------------------------------------------------------------------------- */

namespace egnite {
class LIB_EGNITE_API UndoDock : public QDockWidget {
  Q_OBJECT

 public:
  explicit UndoDock(QWidget *parent = nullptr);
  ~UndoDock() override;

  void setStack(QUndoStack *stack);

 protected:
  void changeEvent(QEvent *event) override;

 private:
  void retranslateUi();

 private:
  QUndoView *m_undo_view;
};
}  // namespace egnite

#endif  // EGNITE_UNDO_DOCK_H
