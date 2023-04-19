/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/document/new_document_widget_factory.h"
/* -------------------------------------------------------------------------- */

namespace flow {
NewDocumentWidgetFactory::NewDocumentWidgetFactory(QIcon icon, QObject *parent)
    : QObject(parent), m_icon(std::move(icon)) {}

NewDocumentWidgetFactory::~NewDocumentWidgetFactory() = default;

void NewDocumentWidgetFactory::setIcon(QIcon icon) { m_icon = std::move(icon); }

QIcon NewDocumentWidgetFactory::getIcon() const { return m_icon; }

}  // namespace flow
