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

  [[nodiscard]] virtual FlowDockWidget* create(
      QWidget* parent = nullptr) const = 0;
};

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::FlowDockWidgetFactory,
                    "org.flow.FlowDockWidgetFactory")

#endif  // FLOW_DOCUMENT_FLOW_DOCK_WIDGET_FACTORY_H
