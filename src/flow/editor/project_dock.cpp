/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/project_dock.h"
/* -------------------------------------------------------------------------- */

ProjectDock::ProjectDock(QWidget *parent)
    : QDockWidget(parent)
{
  setObjectName(QLatin1String("Project"));

  retranslateUi();
}

ProjectDock::~ProjectDock() = default;

void ProjectDock::changeEvent(QEvent *event)
{
  QDockWidget::changeEvent(event);

  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void ProjectDock::retranslateUi()
{
  setWindowTitle(tr("Project"));
}