#ifndef FLOW_DOCUMENT_TOOL_FACTORY_H
#define FLOW_DOCUMENT_TOOL_FACTORY_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/concept.h"
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

namespace flow_document {

/* ---------------------------- SelectionToolFactory ------------------------ */

class FLOW_DOCUMENT_API SelectionToolFactory : public ToolFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::ToolFactory)

 public:
  explicit SelectionToolFactory(QObject* parent = nullptr);
  ~SelectionToolFactory() override;

  [[nodiscard]] Tool* create(QObject* parent = nullptr) const override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_TOOL_FACTORY_H
