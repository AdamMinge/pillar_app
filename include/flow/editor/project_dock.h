#ifndef FLOW_PROJECT_DOCK_H
#define FLOW_PROJECT_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
/* -------------------------------------------------------------------------- */

class ProjectDock : public QDockWidget
{
  Q_OBJECT

public:
  explicit ProjectDock(QWidget *parent = nullptr);
  ~ProjectDock() override;

protected:
  void changeEvent(QEvent *event) override;

private:
  void retranslateUi();
};

#endif//FLOW_PROJECT_DOCK_H
