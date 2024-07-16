/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/flow_dock_widget_factory.h"

#include "flow_document/component/connections/connections_dock.h"
#include "flow_document/component/factories/factories_dock.h"
#include "flow_document/component/layers/layers_dock.h"
#include "flow_document/component/nodes/nodes_dock.h"
#include "flow_document/component/properties/properties_dock.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* --------------------------- FlowDockWidgetFactory ------------------------ */

FlowDockWidgetFactory::FlowDockWidgetFactory(QObject* parent)
    : QObject(parent) {}

FlowDockWidgetFactory::~FlowDockWidgetFactory() = default;

/* ------------------------- FactoriesDockWidgetFactory --------------------- */

FactoriesDockWidgetFactory::FactoriesDockWidgetFactory(QObject* parent)
    : FlowDockWidgetFactory(parent) {}

FactoriesDockWidgetFactory::~FactoriesDockWidgetFactory() = default;

Qt::DockWidgetArea FactoriesDockWidgetFactory::getDockWidgetArea() const {
  return Qt::RightDockWidgetArea;
  ;
}

FlowDockWidget* FactoriesDockWidgetFactory::create(QWidget* parent) const {
  return new FactoriesDock(parent);
}

/* -------------------------- LayersDockWidgetFactory ----------------------- */

LayersDockWidgetFactory::LayersDockWidgetFactory(QObject* parent)
    : FlowDockWidgetFactory(parent) {}

LayersDockWidgetFactory::~LayersDockWidgetFactory() = default;

Qt::DockWidgetArea LayersDockWidgetFactory::getDockWidgetArea() const {
  return Qt::RightDockWidgetArea;
}

FlowDockWidget* LayersDockWidgetFactory::create(QWidget* parent) const {
  return new LayersDock(parent);
}

/* --------------------------- NodesDockWidgetFactory ----------------------- */

NodesDockWidgetFactory::NodesDockWidgetFactory(QObject* parent)
    : FlowDockWidgetFactory(parent) {}

NodesDockWidgetFactory::~NodesDockWidgetFactory() = default;

Qt::DockWidgetArea NodesDockWidgetFactory::getDockWidgetArea() const {
  return Qt::RightDockWidgetArea;
}

FlowDockWidget* NodesDockWidgetFactory::create(QWidget* parent) const {
  return new NodesDock(parent);
}

/* ------------------------ PropertiesDockWidgetFactory --------------------- */

PropertiesDockWidgetFactory::PropertiesDockWidgetFactory(QObject* parent)
    : FlowDockWidgetFactory(parent) {}

PropertiesDockWidgetFactory::~PropertiesDockWidgetFactory() = default;

Qt::DockWidgetArea PropertiesDockWidgetFactory::getDockWidgetArea() const {
  return Qt::LeftDockWidgetArea;
}

FlowDockWidget* PropertiesDockWidgetFactory::create(QWidget* parent) const {
  return new PropertiesDock(parent);
}

/* ------------------------ ConnectionsDockWidgetFactory -------------------- */

ConnectionsDockWidgetFactory::ConnectionsDockWidgetFactory(QObject* parent)
    : FlowDockWidgetFactory(parent) {}

ConnectionsDockWidgetFactory::~ConnectionsDockWidgetFactory() = default;

Qt::DockWidgetArea ConnectionsDockWidgetFactory::getDockWidgetArea() const {
  return Qt::RightDockWidgetArea;
}

FlowDockWidget* ConnectionsDockWidgetFactory::create(QWidget* parent) const {
  return new ConnectionsDock(parent);
}

}  // namespace flow_document
