/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/factory/layer_factory.h"

#include "flow_document/command/add_remove_layer.h"
#include "flow_document/flow/flow.h"
#include "flow_document/flow/group_layer.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow/node_layer.h"
#include "flow_document/flow_document.h"
#include "flow_document/resources.h"
/* ----------------------------------- Utils -------------------------------- */
#include <utils/pointer_cast/unique_ptr_cast.h>
/* -------------------------------------------------------------------------- */

namespace flow_document {

namespace {

/* ----------------------------------- Utils -------------------------------- */

[[nodiscard]] QSet<QString> getAllLayerNames(FlowDocument* document,
                                             const QString& prefix) {
  auto names = QSet<QString>{};
  const auto layers = getAllLayers(document);
  for (const auto layer : layers) {
    if (layer->getName().startsWith(prefix)) names.insert(layer->getName());
  }

  return names;
}

[[nodiscard]] QString getNewDefaultName(FlowDocument* document,
                                        const LayerFactory* factory) {
  auto name_template = factory->getName() + " %1";
  auto names = getAllLayerNames(document, factory->getName());

  auto index = 1;
  auto name = QString{};
  do {
    name = name_template.arg(index);
    ++index;
  } while (names.contains(name));

  return name;
}

}  // namespace

/* -------------------------------- LayerFactory ---------------------------- */

LayerFactory::LayerFactory(QString name, QString section, QObject* parent)
    : LayerFactory(std::move(name), std::move(section),
                   QIcon(icons::x32::Layer), parent) {}

LayerFactory::LayerFactory(QString name, QString section, QIcon icon,
                           QObject* parent)
    : ObjectFactory(type, std::move(name), std::move(section), std::move(icon),
                    parent) {}

LayerFactory::~LayerFactory() = default;

bool LayerFactory::addObject(FlowDocument* document, InitMethod init) const {
  if (!canAddObject(document)) return false;

  auto layer = utils::cast_unique_ptr<Layer>(createObject());
  layer->setName(getNewDefaultName(document, this));
  init(layer.get());

  auto group_layer = document->getFlow()->getRootLayer();
  auto index = group_layer->size();

  if (auto current_layer = document->getCurrentLayer(); current_layer) {
    group_layer = current_layer->getParent();
    index = group_layer->indexOf(current_layer) + 1;
  }

  auto entires = std::list<LayerEntry>{};
  entires.emplace_back(LayerEntry{group_layer, std::move(layer), index});
  document->getUndoStack()->push(new AddLayers(document, std::move(entires)));

  return true;
}

bool LayerFactory::canAddObject(FlowDocument* document) const {
  if (auto current_layer = document->getCurrentLayer(); current_layer) {
    auto parent = current_layer->getParent();
    return parent->isClassOrChild<GroupLayer>();
  }

  return true;
}

/* ----------------------------- GroupLayerFactory -------------------------- */

GroupLayerFactory::GroupLayerFactory(QObject* parent)
    : LayerFactory(tr("Group Layer"), tr("Base"), QIcon(icons::x32::Group),
                   parent) {}

GroupLayerFactory::~GroupLayerFactory() = default;

QString GroupLayerFactory::getObjectClassName() const {
  return GroupLayer::sGetClassName();
}

std::unique_ptr<Object> GroupLayerFactory::createObject() const {
  return std::make_unique<GroupLayer>();
}

/* ------------------------------ NodeLayerFactory -------------------------- */

NodeLayerFactory::NodeLayerFactory(QObject* parent)
    : LayerFactory(tr("Node Layer"), tr("Base"), QIcon(icons::x32::NodeLayer),
                   parent) {}

NodeLayerFactory::~NodeLayerFactory() = default;

QString NodeLayerFactory::getObjectClassName() const {
  return NodeLayer::sGetClassName();
}

std::unique_ptr<Object> NodeLayerFactory::createObject() const {
  return std::make_unique<NodeLayer>();
}

}  // namespace flow_document