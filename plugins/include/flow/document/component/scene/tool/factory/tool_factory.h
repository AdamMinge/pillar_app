#ifndef FLOW_DOCUMENT_TOOL_FACTORY_H
#define FLOW_DOCUMENT_TOOL_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class Tool;

/* -------------------------------- ToolFactory ----------------------------- */

class LIB_FLOW_DOCUMENT_API ToolFactory : public QObject {
  Q_OBJECT

 public:
  explicit ToolFactory(QObject* parent = nullptr);
  ~ToolFactory() override;

  [[nodiscard]] virtual Tool* create(QObject* parent = nullptr) const = 0;
};

}  // namespace flow

Q_DECLARE_INTERFACE(flow::ToolFactory, "org.flow.ToolFactory")

#endif  // FLOW_DOCUMENT_TOOL_FACTORY_H
