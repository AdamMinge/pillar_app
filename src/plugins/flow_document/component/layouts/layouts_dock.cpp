/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/layouts/layouts_dock.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QVBoxLayout>
/* ------------------------------------ Ui ---------------------------------- */
#include "flow_document/ui_layouts_dock.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

LayoutsDock::LayoutsDock(QWidget *parent)
    : QDockWidget(parent), m_ui(new Ui::LayoutsDock()) {
  setObjectName(QLatin1String("Layouts"));

  initUi();
  initConnections();

  retranslateUi();
}

LayoutsDock::~LayoutsDock() = default;

void LayoutsDock::changeEvent(QEvent *event) {
  QDockWidget::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void LayoutsDock::initUi() { m_ui->setupUi(this); }

void LayoutsDock::initConnections() {}

void LayoutsDock::retranslateUi() { m_ui->retranslateUi(this); }

}  // namespace flow_document