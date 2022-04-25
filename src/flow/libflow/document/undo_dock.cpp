/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QVBoxLayout>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/document/undo_dock.h"
/* -------------------------------------------------------------------------- */

namespace flow::document
{

  UndoDock::UndoDock(QWidget *parent)
      : QDockWidget(parent), m_undo_view(new QUndoView(this))
  {
    setObjectName(QLatin1String("History"));

    m_undo_view->setCleanIcon(QIcon(":/editor/images/16x16/undo_clean.png"));

    auto widget = new QWidget(this);
    auto layout = new QVBoxLayout(widget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_undo_view);

    setWidget(widget);
    retranslateUi();
  }

  UndoDock::~UndoDock() = default;

  void UndoDock::setStack(QUndoStack *stack) { m_undo_view->setStack(stack); }

  void UndoDock::changeEvent(QEvent *event)
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

  void UndoDock::retranslateUi()
  {
    setWindowTitle(tr("History"));
    m_undo_view->setEmptyLabel(tr("<empty>"));
  }

}// namespace flow::document
