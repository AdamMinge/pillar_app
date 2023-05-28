/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/properties_browser.h"

#include "flow_document/component/properties/object_properties.h"
#include "flow_document/event/change_event.h"
#include "flow_document/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* -------------------------------------------------------------------------- */

namespace flow_document {

PropertiesBrowser::PropertiesBrowser(QWidget *parent)
    : utils::QtTreePropertyBrowser(parent),
      m_document(nullptr),
      m_current_properties(nullptr) {
  initBrowser();
  initConnections();

  retranslateUi();

  loadObjects();
}

PropertiesBrowser::~PropertiesBrowser() = default;

void PropertiesBrowser::setDocument(FlowDocument *document) {
  if (m_document == document) return;

  if (m_document) {
    disconnect(m_document, &FlowDocument::currentObjectChanged, this,
               &PropertiesBrowser::onCurrentObjectChanged);
  }

  m_document = document;

  if (m_document) {
    connect(m_document, &FlowDocument::currentObjectChanged, this,
            &PropertiesBrowser::onCurrentObjectChanged);
  }
}

FlowDocument *PropertiesBrowser::getDocument() const { return m_document; }

void PropertiesBrowser::changeEvent(QEvent *event) {
  utils::QtTreePropertyBrowser::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void PropertiesBrowser::addedObject(ObjectProperties *object_properties) {
  m_class_to_properties.insert(object_properties->supportedClass(),
                               object_properties);
}

void PropertiesBrowser::removedObject(ObjectProperties *object_properties) {
  m_class_to_properties.remove(object_properties->supportedClass());
}

void PropertiesBrowser::onEvent(const ChangeEvent &event) {
  if (m_current_properties) m_current_properties->onEvent(event);
}

void PropertiesBrowser::onCurrentObjectChanged(Object *object) {
  auto object_properties = static_cast<ObjectProperties *>(nullptr);

  if (object) {
    auto inherited_classes = object->inheritedClasses();
    qDebug() << "inherited_classes = " << inherited_classes;

    for (const auto &inherited_class : inherited_classes) {
      if (m_class_to_properties.contains(inherited_class)) {
        object_properties = m_class_to_properties[inherited_class];
        break;
      }
    }
  }

  qDebug() << "m_current_properties = " << object_properties;
  if (m_current_properties == object_properties) return;

  m_current_properties = object_properties;

  clear();
  if (m_current_properties)
    addProperty(m_current_properties->getRootProperty());
}

void PropertiesBrowser::initBrowser() {
  setResizeMode(ResizeMode::ResizeToContents);
  setRootIsDecorated(false);
  setPropertiesWithoutValueMarked(true);
}

void PropertiesBrowser::initConnections() {}

void PropertiesBrowser::retranslateUi() {}

}  // namespace flow_document