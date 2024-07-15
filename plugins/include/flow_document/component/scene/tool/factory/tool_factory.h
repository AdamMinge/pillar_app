#ifndef FLOW_DOCUMENT_TOOL_FACTORY_H
#define FLOW_DOCUMENT_TOOL_FACTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class Tool;

/* -------------------------------- ToolFactory ----------------------------- */

class FLOW_DOCUMENT_API ToolFactory : public QObject {
  Q_OBJECT

 public:
  explicit ToolFactory(QObject* parent = nullptr);
  ~ToolFactory() override;

  [[nodiscard]] virtual Tool* create(QObject* parent = nullptr) const = 0;
};

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::ToolFactory, "org.flow.ToolFactory")

#endif  // FLOW_DOCUMENT_TOOL_FACTORY_H
