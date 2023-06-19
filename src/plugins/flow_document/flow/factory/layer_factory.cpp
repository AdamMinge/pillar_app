/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/factory/layer_factory.h"

#include "flow_document/flow/group_layer.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow/node_layer.h"
#include "flow_document/resources.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* -------------------------------- LayerFactory ---------------------------- */

LayerFactory::LayerFactory(QString name, QString section, QObject* parent)
    : LayerFactory(std::move(name), std::move(section),
                   QIcon(icons::x32::Layer), parent) {}

LayerFactory::LayerFactory(QString name, QString section, QIcon icon,
                           QObject* parent)
    : Factory(Type::LayerFactory, std::move(name), std::move(section),
              std::move(icon), parent) {}

LayerFactory::~LayerFactory() = default;

/* ----------------------------- GroupLayerFactory -------------------------- */

GroupLayerFactory::GroupLayerFactory(QObject* parent)
    : LayerFactory(tr("Group Layer"), tr("Base"), QIcon(icons::x32::Group),
                   parent) {}

GroupLayerFactory::~GroupLayerFactory() = default;

QString GroupLayerFactory::getObjectClass() const {
  return GroupLayer::getStaticClassName();
}

std::unique_ptr<Object> GroupLayerFactory::create() const {
  return std::make_unique<GroupLayer>();
}

/* ------------------------------ NodeLayerFactory -------------------------- */

NodeLayerFactory::NodeLayerFactory(QObject* parent)
    : LayerFactory(tr("Node Layer"), tr("Base"), QIcon(icons::x32::NodeLayer),
                   parent) {}

NodeLayerFactory::~NodeLayerFactory() = default;

QString NodeLayerFactory::getObjectClass() const {
  return NodeLayer::getStaticClassName();
}

std::unique_ptr<Object> NodeLayerFactory::create() const {
  return std::make_unique<NodeLayer>();
}

}  // namespace flow_document