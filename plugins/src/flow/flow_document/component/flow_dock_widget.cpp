/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/flow_dock_widget.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowDockWidget::FlowDockWidget(QWidget *parent)
    : QDockWidget(parent), m_document(nullptr) {}

FlowDockWidget::~FlowDockWidget() = default;

void FlowDockWidget::setDocument(FlowDocument *document) {
  if (m_document == document) return;

  auto from_document = m_document;
  m_document = document;

  Q_EMIT onDocumentChanged(from_document, m_document);
}

FlowDocument *FlowDockWidget::getDocument() const { return m_document; }

void FlowDockWidget::onDocumentChanged(FlowDocument *from, FlowDocument *to) {}

}  // namespace flow_document
