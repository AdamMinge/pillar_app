#ifndef FLOW_UNDO_DOCK_H
#define FLOW_UNDO_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QUndoStack>
#include <QUndoView>
/* -------------------------------------------------------------------------- */

class UndoDock : public QDockWidget
{
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

#endif//FLOW_UNDO_DOCK_H
