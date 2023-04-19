/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/document/new_document_widget.h"
/* -------------------------------------------------------------------------- */

namespace flow {

NewDocumentWidget::NewDocumentWidget(QWidget *parent)
    : QWidget(parent), m_valid(false) {}

NewDocumentWidget::~NewDocumentWidget() = default;

bool NewDocumentWidget::isValid() const { return m_valid; }

void NewDocumentWidget::setValid(bool valid) {
  if (m_valid != valid) {
    m_valid = valid;
    Q_EMIT isValidChanged(m_valid);
  }
}

}  // namespace flow
