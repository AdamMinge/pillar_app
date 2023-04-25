#ifndef FLOW_DOCUMENT_ADD_REMOVE_NODE_H
#define FLOW_DOCUMENT_ADD_REMOVE_NODE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QPointF>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/command/command.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowNode;
class FlowDocument;

class FLOW_DOCUMENT_API AddRemoveNodeCommand : public egnite::Command {
 public:
  explicit AddRemoveNodeCommand(QString name, FlowDocument *document,
                                FlowNode *node_to_remove,
                                egnite::Command *parent = nullptr);
  explicit AddRemoveNodeCommand(QString name, FlowDocument *document,
                                const QString &node_to_create_id,
                                const QPointF &pos,
                                egnite::Command *parent = nullptr);
  ~AddRemoveNodeCommand() override;

 protected:
  void addNode();
  void removeNode();

 private:
  FlowDocument *m_document;
  FlowNode *m_node_to_remove;
  FlowNode *m_node_to_add;
};

class AddNodeCommand : public AddRemoveNodeCommand {
 public:
  explicit AddNodeCommand(FlowDocument *document,
                          const QString &node_to_create_id, const QPointF &pos,
                          egnite::Command *parent = nullptr);
  ~AddNodeCommand() override;

  void redo() override;
  void undo() override;
};

class RemoveNodeCommand : public AddRemoveNodeCommand {
 public:
  explicit RemoveNodeCommand(FlowDocument *document, FlowNode *node_to_remove,
                             egnite::Command *parent = nullptr);
  ~RemoveNodeCommand() override;

  void redo() override;
  void undo() override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_ADD_REMOVE_NODE_H
