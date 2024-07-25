#ifndef FLOW_DOCUMENT_FLOW_DOCK_WIDGET_FACTORY_H
#define FLOW_DOCUMENT_FLOW_DOCK_WIDGET_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/concept.h"
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class FlowDockWidget;

/* --------------------------- FlowDockWidgetFactory ------------------------ */

class LIB_FLOW_DOCUMENT_API FlowDockWidgetFactory : public QObject {
  Q_OBJECT

 public:
  explicit FlowDockWidgetFactory(QObject* parent = nullptr);
  ~FlowDockWidgetFactory() override;

  [[nodiscard]] virtual Qt::DockWidgetArea getDockWidgetArea() const = 0;
  [[nodiscard]] virtual FlowDockWidget* create(
      QWidget* parent = nullptr) const = 0;
};

}  // namespace flow

Q_DECLARE_INTERFACE(flow::FlowDockWidgetFactory,
                    "org.flow.FlowDockWidgetFactory")

namespace flow {

/* ------------------------- FactoriesDockWidgetFactory --------------------- */

class LIB_FLOW_DOCUMENT_API FactoriesDockWidgetFactory
    : public FlowDockWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(flow::FlowDockWidgetFactory)

 public:
  explicit FactoriesDockWidgetFactory(QObject* parent = nullptr);
  ~FactoriesDockWidgetFactory() override;

  [[nodiscard]] Qt::DockWidgetArea getDockWidgetArea() const override;
  [[nodiscard]] FlowDockWidget* create(
      QWidget* parent = nullptr) const override;
};

/* -------------------------- LayersDockWidgetFactory ----------------------- */

class LIB_FLOW_DOCUMENT_API LayersDockWidgetFactory
    : public FlowDockWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(flow::FlowDockWidgetFactory)

 public:
  explicit LayersDockWidgetFactory(QObject* parent = nullptr);
  ~LayersDockWidgetFactory() override;

  [[nodiscard]] Qt::DockWidgetArea getDockWidgetArea() const override;
  [[nodiscard]] FlowDockWidget* create(
      QWidget* parent = nullptr) const override;
};

/* --------------------------- NodesDockWidgetFactory ----------------------- */

class LIB_FLOW_DOCUMENT_API NodesDockWidgetFactory
    : public FlowDockWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(flow::FlowDockWidgetFactory)

 public:
  explicit NodesDockWidgetFactory(QObject* parent = nullptr);
  ~NodesDockWidgetFactory() override;

  [[nodiscard]] Qt::DockWidgetArea getDockWidgetArea() const override;
  [[nodiscard]] FlowDockWidget* create(
      QWidget* parent = nullptr) const override;
};

/* ------------------------ PropertiesDockWidgetFactory --------------------- */

class LIB_FLOW_DOCUMENT_API PropertiesDockWidgetFactory
    : public FlowDockWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(flow::FlowDockWidgetFactory)

 public:
  explicit PropertiesDockWidgetFactory(QObject* parent = nullptr);
  ~PropertiesDockWidgetFactory() override;

  [[nodiscard]] Qt::DockWidgetArea getDockWidgetArea() const override;
  [[nodiscard]] FlowDockWidget* create(
      QWidget* parent = nullptr) const override;
};

/* ------------------------ ConnectionsDockWidgetFactory -------------------- */

class LIB_FLOW_DOCUMENT_API ConnectionsDockWidgetFactory
    : public FlowDockWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(flow::FlowDockWidgetFactory)

 public:
  explicit ConnectionsDockWidgetFactory(QObject* parent = nullptr);
  ~ConnectionsDockWidgetFactory() override;

  [[nodiscard]] Qt::DockWidgetArea getDockWidgetArea() const override;
  [[nodiscard]] FlowDockWidget* create(
      QWidget* parent = nullptr) const override;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_FLOW_DOCK_WIDGET_FACTORY_H
