/* ----------------------------------- Local -------------------------------- */
#include "pillar/document/new_document_widget_factory.h"
/* -------------------------------------------------------------------------- */

namespace pillar {
NewDocumentWidgetFactory::NewDocumentWidgetFactory(QIcon icon, QObject *parent)
    : QObject(parent), m_icon(std::move(icon)) {}

NewDocumentWidgetFactory::~NewDocumentWidgetFactory() = default;

void NewDocumentWidgetFactory::setIcon(QIcon icon) { m_icon = std::move(icon); }

QIcon NewDocumentWidgetFactory::getIcon() const { return m_icon; }

}  // namespace pillar
