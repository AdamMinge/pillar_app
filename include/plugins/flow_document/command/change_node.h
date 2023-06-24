#ifndef FLOW_DOCUMENT_CHANGE_NODE_H
#define FLOW_DOCUMENT_CHANGE_NODE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QVariantMap>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/change_value.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class Node;

/* ------------------------------ SetNodesVisible --------------------------- */

class FLOW_DOCUMENT_API SetNodesVisible : public ChangeValue<Node, bool> {
 public:
  explicit SetNodesVisible(FlowDocument* document, QList<Node*> nodes,
                           bool visible, Command* parent = nullptr);
  ~SetNodesVisible() override;

 protected:
  [[nodiscard]] bool getValue(const Node* node) const override;
  void setValue(Node* node, const bool& visible) override;
};

/* ------------------------------- SetNodesName ----------------------------- */

class FLOW_DOCUMENT_API SetNodesName : public ChangeValue<Node, QString> {
 public:
  explicit SetNodesName(FlowDocument* document, QList<Node*> nodes,
                        QString name, Command* parent = nullptr);
  ~SetNodesName() override;

 protected:
  [[nodiscard]] QString getValue(const Node* node) const override;
  void setValue(Node* node, const QString& name) override;
};

/* ------------------------------ SetNodesPosition -------------------------- */

class FLOW_DOCUMENT_API SetNodesPosition : public ChangeValue<Node, QPointF> {
 public:
  explicit SetNodesPosition(FlowDocument* document, QList<Node*> nodes,
                            QPointF position, Command* parent = nullptr);
  ~SetNodesPosition() override;

 protected:
  [[nodiscard]] QPointF getValue(const Node* node) const override;
  void setValue(Node* node, const QPointF& position) override;
};

/* -------------------------- SetNodesCustomProperty ------------------------ */

class FLOW_DOCUMENT_API SetNodesCustomProperty
    : public ChangeValue<Node, QVariant> {
 public:
  explicit SetNodesCustomProperty(FlowDocument* document, QList<Node*> nodes,
                                  QString property, QVariant value,
                                  Command* parent = nullptr);
  ~SetNodesCustomProperty() override;

 protected:
  [[nodiscard]] QVariant getValue(const Node* node) const override;
  void setValue(Node* node, const QVariant& value) override;

 private:
  QString m_property;
};

/* ------------------------- AddRemoveNodesProperties ----------------------- */

class FLOW_DOCUMENT_API AddRemoveNodesProperties : public egnite::Command {
 public:
  explicit AddRemoveNodesProperties(QString name, FlowDocument* document,
                                    QList<Node*> nodes, QVariantMap properties,
                                    Command* parent = nullptr);
  ~AddRemoveNodesProperties() override;

 protected:
  void addProperties();
  void removeProperties();

 protected:
  FlowDocument* m_document;
  QList<Node*> m_nodes;
  QVariantMap m_properties;
};

/* ---------------------------- AddNodesProperties -------------------------- */

class FLOW_DOCUMENT_API AddNodesProperties : public AddRemoveNodesProperties {
 public:
  explicit AddNodesProperties(FlowDocument* document, QList<Node*> nodes,
                              QVariantMap properties,
                              Command* parent = nullptr);
  ~AddNodesProperties() override;

  void undo() override;
  void redo() override;
};

/* --------------------------- RemoveNodesProperties ------------------------ */

class FLOW_DOCUMENT_API RemoveNodesProperties
    : public AddRemoveNodesProperties {
 public:
  explicit RemoveNodesProperties(FlowDocument* document, QList<Node*> nodes,
                                 QStringList properties,
                                 Command* parent = nullptr);
  ~RemoveNodesProperties() override;

  void undo() override;
  void redo() override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CHANGE_NODE_H