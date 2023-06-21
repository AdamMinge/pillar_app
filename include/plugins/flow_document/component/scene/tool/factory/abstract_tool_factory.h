#ifndef FLOW_DOCUMENT_ABSTRACT_TOOL_FACTORY_H
#define FLOW_DOCUMENT_ABSTRACT_TOOL_FACTORY_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/concept.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class AbstractTool;

/* ---------------------------- AbstractToolFactory ------------------------- */

class FLOW_DOCUMENT_API AbstractToolFactory : public QObject {
  Q_OBJECT

 public:
  explicit AbstractToolFactory(QObject* parent = nullptr);
  ~AbstractToolFactory() override;

  [[nodiscard]] virtual AbstractTool* create(
      QObject* parent = nullptr) const = 0;
};

}  // namespace flow_document

Q_DECLARE_INTERFACE(flow_document::AbstractToolFactory,
                    "org.flow.AbstractToolFactory")

namespace flow_document {

/* ---------------------------- SelectionToolFactory ------------------------ */

class FLOW_DOCUMENT_API SelectionToolFactory : public AbstractToolFactory {
  Q_OBJECT
  Q_INTERFACES(flow_document::AbstractToolFactory)

 public:
  explicit SelectionToolFactory(QObject* parent = nullptr);
  ~SelectionToolFactory() override;

  [[nodiscard]] AbstractTool* create(QObject* parent = nullptr) const override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_ABSTRACT_TOOL_FACTORY_H
