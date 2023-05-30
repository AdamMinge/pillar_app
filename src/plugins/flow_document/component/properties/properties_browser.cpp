/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/properties_browser.h"

#include "flow_document/component/properties/object_properties.h"
#include "flow_document/event/change_event.h"
#include "flow_document/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
/* -------------------------------------------------------------------------- */
/* ----------------------------------- Utils -------------------------------- */
#include <utils/property_browser/editor_factory.h>
#include <utils/property_browser/property_manager.h>
#include <utils/property_browser/tree_property_browser.h>
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
    disconnect(m_document, &FlowDocument::event, this,
               &PropertiesBrowser::onEvent);
  }

  m_document = document;

  if (m_document) {
    connect(m_document, &FlowDocument::currentObjectChanged, this,
            &PropertiesBrowser::onCurrentObjectChanged);
    connect(m_document, &FlowDocument::event, this,
            &PropertiesBrowser::onEvent);
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
  auto object_properties = getPropertiesByObject(object);

  if (m_current_properties) {
    m_current_properties->unsetFactoryForManager(this);
    m_current_properties->setObject(nullptr);
  }

  m_current_properties = object_properties;

  if (m_current_properties) {
    m_current_properties->setFactoryForManager(this);
    m_current_properties->setObject(object);
  }

  clear();

  if (m_current_properties) {
    for (auto property : m_current_properties->getProperties())
      addProperty(property);
  }
}

void PropertiesBrowser::initBrowser() {
  setResizeMode(ResizeMode::ResizeToContents);
  setRootIsDecorated(false);
  setPropertiesWithoutValueMarked(true);
}

void PropertiesBrowser::initConnections() {}

void PropertiesBrowser::retranslateUi() {}

ObjectProperties *PropertiesBrowser::getPropertiesByObject(
    Object *object) const {
  auto object_properties = static_cast<ObjectProperties *>(nullptr);

  if (object) {
    auto inherited_classes = object->inheritedClasses();
    inherited_classes.prepend(object->className());

    for (const auto &inherited_class : inherited_classes) {
      if (m_class_to_properties.contains(inherited_class)) {
        object_properties = m_class_to_properties[inherited_class];
        break;
      }
    }
  }

  return object_properties;
}

}  // namespace flow_document