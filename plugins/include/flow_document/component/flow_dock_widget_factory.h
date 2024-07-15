#ifndef FLOW_DOCUMENT_FLOW_DOCK_WIDGET_FACTORY_H
#define FLOW_DOCUMENT_FLOW_DOCK_WIDGET_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/concept.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDockWidget;

/* --------------------------- FlowDockWidgetFactory ------------------------ */

class FLOW_DOCUMENT_API FlowDockWidgetFactory : public QObject {
  Q_OBJECT

 public:
  explicit FlowDockWidgetFactory(QObject* parent = nullptr);
  ~FlowDockWidgetFactory() override;

  [[nodiscard]] virtual Qt::DockWidgetArea getDockWidgetArea() const = 0;
  [[nodiscard]] virtual FlowDockWidget* create(
      QWidget* parent = nullptr) const = 0;
};

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::FlowDockWidgetFactory,
                    "org.flow.FlowDockWidgetFactory")

namespace flow_document {

/* ------------------------- FactoriesDockWidgetFactory --------------------- */

class FLOW_DOCUMENT_API FactoriesDockWidgetFactory
    : public FlowDockWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::FlowDockWidgetFactory)

 public:
  explicit FactoriesDockWidgetFactory(QObject* parent = nullptr);
  ~FactoriesDockWidgetFactory() override;

  [[nodiscard]] Qt::DockWidgetArea getDockWidgetArea() const override;
  [[nodiscard]] FlowDockWidget* create(
      QWidget* parent = nullptr) const override;
};

/* -------------------------- LayersDockWidgetFactory ----------------------- */

class FLOW_DOCUMENT_API LayersDockWidgetFactory : public FlowDockWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::FlowDockWidgetFactory)

 public:
  explicit LayersDockWidgetFactory(QObject* parent = nullptr);
  ~LayersDockWidgetFactory() override;

  [[nodiscard]] Qt::DockWidgetArea getDockWidgetArea() const override;
  [[nodiscard]] FlowDockWidget* create(
      QWidget* parent = nullptr) const override;
};

/* --------------------------- NodesDockWidgetFactory ----------------------- */

class FLOW_DOCUMENT_API NodesDockWidgetFactory : public FlowDockWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::FlowDockWidgetFactory)

 public:
  explicit NodesDockWidgetFactory(QObject* parent = nullptr);
  ~NodesDockWidgetFactory() override;

  [[nodiscard]] Qt::DockWidgetArea getDockWidgetArea() const override;
  [[nodiscard]] FlowDockWidget* create(
      QWidget* parent = nullptr) const override;
};

/* ------------------------ PropertiesDockWidgetFactory --------------------- */

class FLOW_DOCUMENT_API PropertiesDockWidgetFactory
    : public FlowDockWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::FlowDockWidgetFactory)

 public:
  explicit PropertiesDockWidgetFactory(QObject* parent = nullptr);
  ~PropertiesDockWidgetFactory() override;

  [[nodiscard]] Qt::DockWidgetArea getDockWidgetArea() const override;
  [[nodiscard]] FlowDockWidget* create(
      QWidget* parent = nullptr) const override;
};

/* ------------------------ ConnectionsDockWidgetFactory -------------------- */

class FLOW_DOCUMENT_API ConnectionsDockWidgetFactory
    : public FlowDockWidgetFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::FlowDockWidgetFactory)

 public:
  explicit ConnectionsDockWidgetFactory(QObject* parent = nullptr);
  ~ConnectionsDockWidgetFactory() override;

  [[nodiscard]] Qt::DockWidgetArea getDockWidgetArea() const override;
  [[nodiscard]] FlowDockWidget* create(
      QWidget* parent = nullptr) const override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_DOCK_WIDGET_FACTORY_H
