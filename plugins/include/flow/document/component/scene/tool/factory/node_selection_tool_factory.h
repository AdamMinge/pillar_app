#ifndef FLOW_DOCUMENT_NODE_SELECTION_TOOL_FACTORY_H
#define FLOW_DOCUMENT_NODE_SELECTION_TOOL_FACTORY_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/scene/tool/factory/tool_factory.h"
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* -------------------------- NodeSelectionToolFactory ---------------------- */

class LIB_FLOW_DOCUMENT_API NodeSelectionToolFactory : public ToolFactory {
  Q_OBJECT
  Q_INTERFACES(flow::ToolFactory)

 public:
  explicit NodeSelectionToolFactory(QObject* parent = nullptr);
  ~NodeSelectionToolFactory() override;

  [[nodiscard]] Tool* create(QObject* parent = nullptr) const override;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_NODE_SELECTION_TOOL_FACTORY_H
