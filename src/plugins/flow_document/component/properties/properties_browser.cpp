/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/properties_browser.h"

#include "flow_document/component/properties/object_properties.h"
#include "flow_document/event/change_event.h"
#include "flow_document/flow_document.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QRegularExpression>
#include <QTreeWidgetItemIterator>
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
    disconnect(m_document, &FlowDocument::event, this,
               &PropertiesBrowser::onEvent);
  }

  m_document = document;

  onCurrentObjectChanged(m_document->getCurrentObject());
  filterProperties();

  if (m_document) {
    connect(m_document, &FlowDocument::currentObjectChanged, this,
            &PropertiesBrowser::onCurrentObjectChanged);
    connect(m_document, &FlowDocument::event, this,
            &PropertiesBrowser::onEvent);
  }
}

FlowDocument *PropertiesBrowser::getDocument() const { return m_document; }

void PropertiesBrowser::setFilter(const QString &filter) {
  if (m_filter == filter) return;

  m_filter = filter;
  filterProperties();
}

QString PropertiesBrowser::getFilter() const { return m_filter; }

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

void PropertiesBrowser::filterProperties() {
  for (auto item : topLevelItems()) filterProperty(item);
}

bool PropertiesBrowser::filterProperty(utils::QtBrowserItem *item) {
  const auto property_name = item->property()->propertyName();
  const auto item_matched =
      property_name.contains(m_filter, Qt::CaseInsensitive);

  auto any_children_matched = false;
  for (auto child : item->children()) {
    any_children_matched |= filterProperty(child);
  }

  const auto visible = item_matched || any_children_matched;
  setItemVisible(item, visible);

  return visible;
}

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