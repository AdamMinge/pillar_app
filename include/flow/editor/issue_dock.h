#ifndef FLOW_ISSUE_DOCK_H
#define FLOW_ISSUE_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
/* -------------------------------------------------------------------------- */

class IssueDock : public QDockWidget
{
  Q_OBJECT

public:
  explicit IssueDock(QWidget *parent = nullptr);
  ~IssueDock() override;

protected:
  void changeEvent(QEvent *event) override;

private:
  void retranslateUi();
};

#endif//FLOW_ISSUE_DOCK_H
