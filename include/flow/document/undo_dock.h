#ifndef FLOW_UNDO_DOCK_H
#define FLOW_UNDO_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QUndoStack>
#include <QUndoView>
/* ----------------------------------- Local -------------------------------- */
#include "flow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {
class LIB_FLOW_API UndoDock : public QDockWidget {
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
}  // namespace flow

#endif  // FLOW_UNDO_DOCK_H
