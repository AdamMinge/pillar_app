/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/properties_dock.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QToolBar>
#include <QVBoxLayout>
/* ----------------------------------- Utils -------------------------------- */
#include <utils/action/action.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "flow_document/ui_properties_dock.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

PropertiesDock::PropertiesDock(QWidget *parent)
    : QDockWidget(parent), m_document(nullptr), m_ui(new Ui::PropertiesDock()) {
  setObjectName(QLatin1String("Properties"));

  initUi();
  initConnections();

  retranslateUi();
}

PropertiesDock::~PropertiesDock() = default;

void PropertiesDock::setDocument(FlowDocument *document) {
  if (m_document == document) return;

  m_document = document;

  m_ui->m_properties_browser->setDocument(m_document);
}

FlowDocument *PropertiesDock::getDocument() const { return m_document; }

void PropertiesDock::changeEvent(QEvent *event) {
  QDockWidget::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void PropertiesDock::searchProperties(const QString &search) {
  m_ui->m_properties_browser->setFilter(search);
}

void PropertiesDock::initUi() {
  m_ui->setupUi(this);

  auto buttons_container = new QToolBar();
  buttons_container->setFloatable(false);
  buttons_container->setMovable(false);
  buttons_container->setIconSize(QSize(16, 16));

  buttons_container->addAction(
      m_ui->m_properties_browser->getAddPropertyAction());
  buttons_container->addAction(
      m_ui->m_properties_browser->getRemovePropertyAction());

  m_ui->m_toolbar_layout->addWidget(buttons_container);
}

void PropertiesDock::initConnections() {
  connect(m_ui->m_search_properties_edit, &QLineEdit::textChanged, this,
          &PropertiesDock::searchProperties);
}

void PropertiesDock::retranslateUi() { m_ui->retranslateUi(this); }

}  // namespace flow_document