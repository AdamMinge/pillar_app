/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/properties/properties_browser.h"

#include "flow_document/command/change_layer.h"
#include "flow_document/command/change_node.h"
#include "flow_document/component/properties/create_property.h"
#include "flow_document/component/properties/object_properties.h"
#include "flow_document/component/properties/object_properties_factory.h"
#include "flow_document/flow_document.h"
#include "flow_document/resources.h"
/* ----------------------------------- Utils -------------------------------- */
#include <utils/action/action.h>
/* ------------------------------------ Qt ---------------------------------- */
#include <QContextMenuEvent>
#include <QEvent>
#include <QMenu>
/* -------------------------------------------------------------------------- */

namespace flow_document {

PropertiesBrowser::PropertiesBrowser(QWidget *parent)
    : utils::QtTreePropertyBrowser(parent),
      m_document(nullptr),
      m_current_properties(nullptr),
      m_add_property(utils::createActionWithShortcut(QKeySequence{}, this)),
      m_remove_property(utils::createActionWithShortcut(QKeySequence{}, this)) {
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

  onCurrentObjectChanged(m_document ? m_document->getCurrentObject() : nullptr);
  filterProperties();

  if (m_document) {
    connect(m_document, &FlowDocument::currentObjectChanged, this,
            &PropertiesBrowser::onCurrentObjectChanged);
  }
}

FlowDocument *PropertiesBrowser::getDocument() const { return m_document; }

void PropertiesBrowser::setFilter(const QString &filter) {
  if (m_filter == filter) return;

  m_filter = filter;
  filterProperties();
}

QString PropertiesBrowser::getFilter() const { return m_filter; }

QAction *PropertiesBrowser::getAddPropertyAction() const {
  return m_add_property;
}

QAction *PropertiesBrowser::getRemovePropertyAction() const {
  return m_remove_property;
}

void PropertiesBrowser::contextMenuEvent(QContextMenuEvent *event) {
  QMenu menu;
  menu.addAction(m_add_property);
  menu.addAction(m_remove_property);

  menu.exec(event->globalPos());
}

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

void PropertiesBrowser::addedObject(ObjectPropertiesFactory *factory) {
  m_properties_factories.append(factory);
}

void PropertiesBrowser::removedObject(ObjectPropertiesFactory *factory) {
  m_properties_factories.removeOne(factory);
}

void PropertiesBrowser::onCurrentObjectChanged(Object *object) {
  auto current_properties = getPropertiesByObject(object);

  if (m_current_properties && m_current_properties != current_properties) {
    m_current_properties->unsetFactoryForManager(this);
    m_current_properties->setDocument(nullptr);
    m_current_properties->setObject(nullptr);
  }

  m_current_properties = current_properties;

  if (m_current_properties) {
    m_current_properties->setFactoryForManager(this);
    m_current_properties->setDocument(m_document);
    m_current_properties->setObject(object);
  }

  clear();
  updateActions();

  if (m_current_properties) {
    for (auto property : m_current_properties->getProperties())
      addProperty(property);
  }
}

void PropertiesBrowser::onAddProperty() {
  Q_ASSERT(m_current_properties);
  Q_ASSERT(m_current_properties->getObject());

  CreateProperty create_property(m_current_properties->getObject());
  if (create_property.exec() == QDialog::Accepted) {
    auto property_name = create_property.getPropertyName();
    auto property_type = QVariant(create_property.getPropertyType());

    m_current_properties->addProperty(property_name, property_type);
  }
}

void PropertiesBrowser::onRemoveProperty() {
  const auto property = currentItem() ? currentItem()->property() : nullptr;
  Q_ASSERT(property);

  Q_ASSERT(m_current_properties);
  Q_ASSERT(m_current_properties->isCustomProperty(property));
  m_current_properties->removeProperty(property->propertyName());
}

void PropertiesBrowser::updateActions() {
  auto enable_add_property = false;
  auto enable_remove_property = false;

  if (m_current_properties) {
    const auto item = currentItem();
    const auto property = item ? item->property() : nullptr;

    const auto has_object = m_current_properties->getObject() != nullptr;
    const auto is_custom = m_current_properties->isCustomProperty(property);

    enable_add_property = has_object;
    enable_remove_property = is_custom;
  }

  m_add_property->setEnabled(enable_add_property);
  m_remove_property->setEnabled(enable_remove_property);
}

void PropertiesBrowser::initBrowser() {
  setResizeMode(ResizeMode::ResizeToContents);
  setRootIsDecorated(false);
  setPropertiesWithoutValueMarked(true);

  m_add_property->setIcon(QIcon(icons::x16::Add));
  m_remove_property->setIcon(QIcon(icons::x16::Remove));
}

void PropertiesBrowser::initConnections() {
  connect(m_add_property, &QAction::triggered, this,
          &PropertiesBrowser::onAddProperty);
  connect(m_remove_property, &QAction::triggered, this,
          &PropertiesBrowser::onRemoveProperty);

  connect(this, &PropertiesBrowser::currentItemChanged, this,
          &PropertiesBrowser::updateActions);
}

void PropertiesBrowser::retranslateUi() {
  m_add_property->setText(tr("&Add Property"));
  m_add_property->setWhatsThis(tr("Add Property"));

  m_remove_property->setText(tr("&Remove Property"));
  m_remove_property->setWhatsThis(tr("Remove Selected Property"));
}

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

ObjectPropertiesFactory *PropertiesBrowser::getFactoryByObject(Object *object) {
  if (object) {
    auto inherited_classes = object->inheritedClasses();
    inherited_classes.prepend(object->className());

    for (const auto &inherited_class : inherited_classes) {
      auto found_factory = std::find_if(
          m_properties_factories.cbegin(), m_properties_factories.cend(),
          [&inherited_class](const auto &factory) {
            return factory->supportedClass() == inherited_class;
          });

      if (found_factory != m_properties_factories.cend()) return *found_factory;
    }
  }

  return nullptr;
}

ObjectProperties *PropertiesBrowser::getPropertiesByObject(Object *object) {
  auto factory = getFactoryByObject(object);
  if (!factory) return nullptr;

  if (!m_factories_to_properties.contains(factory)) {
    m_factories_to_properties.insert(factory, factory->create(this));
  }

  return m_factories_to_properties[factory];
}

}  // namespace flow_document