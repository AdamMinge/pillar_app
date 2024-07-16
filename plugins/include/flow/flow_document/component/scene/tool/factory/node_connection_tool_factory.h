#ifndef FLOW_DOCUMENT_NODE_CONNECTION_TOOL_FACTORY_H
#define FLOW_DOCUMENT_NODE_CONNECTION_TOOL_FACTORY_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/tool/factory/tool_factory.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* -------------------------- NodeConnectionToolFactory --------------------- */

class FLOW_DOCUMENT_API NodeConnectionToolFactory : public ToolFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::ToolFactory)

 public:
  explicit NodeConnectionToolFactory(QObject* parent = nullptr);
  ~NodeConnectionToolFactory() override;

  [[nodiscard]] Tool* create(QObject* parent = nullptr) const override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NODE_CONNECTION_TOOL_FACTORY_H
