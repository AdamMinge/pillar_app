#ifndef FLOW_DOCUMENT_NODE_CONNECTION_TOOL_FACTORY_H
#define FLOW_DOCUMENT_NODE_CONNECTION_TOOL_FACTORY_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/scene/tool/factory/tool_factory.h"
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

/* -------------------------- NodeConnectionToolFactory --------------------- */

class LIB_FLOW_DOCUMENT_API NodeConnectionToolFactory : public ToolFactory {
  Q_OBJECT
  Q_INTERFACES(flow::ToolFactory)

 public:
  explicit NodeConnectionToolFactory(QObject* parent = nullptr);
  ~NodeConnectionToolFactory() override;

  [[nodiscard]] Tool* create(QObject* parent = nullptr) const override;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_NODE_CONNECTION_TOOL_FACTORY_H
