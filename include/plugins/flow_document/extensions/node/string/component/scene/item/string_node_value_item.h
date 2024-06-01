#ifndef STRING_NODE_VALUE_ITEM_H
#define STRING_NODE_VALUE_ITEM_H

/* ------------------------------------- Qt --------------------------------- */
#include <QLineEdit>
#include <QScopedPointer>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow_document/component/scene/item/node_item.h>
/* ----------------------------------- Local -------------------------------- */
#include "export.h"
/* -------------------------------------------------------------------------- */

class StringNodeStringEmittersChangeEvent;
class StringNodeStringEmitter;
class StringNodeStringReceiver;

/* ------------------------ StringNodeStringEmitterItem --------------------- */

class STRING_NODE_API StringNodeStringEmitterItem
    : public flow_document::NodeItem {
  Q_OBJECT

 public:
  explicit StringNodeStringEmitterItem(StringNodeStringEmitter *node,
                                       flow_document::FlowDocument *document,
                                       QGraphicsItem *parent);
  ~StringNodeStringEmitterItem() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

 protected Q_SLOTS:
  void onEvent(const flow_document::ChangeEvent &event) override;
  void onUpdate(const StringNodeStringEmittersChangeEvent &event);

 private:
  void apply();

 private:
  QScopedPointer<QLineEdit> m_widget;
  bool m_updating;
};

/* ------------------------ StringNodeStringReceiverItem -------------------- */

class STRING_NODE_API StringNodeStringReceiverItem
    : public flow_document::NodeItem {
  Q_OBJECT

 public:
  explicit StringNodeStringReceiverItem(StringNodeStringReceiver *node,
                                        flow_document::FlowDocument *document,
                                        QGraphicsItem *parent);
  ~StringNodeStringReceiverItem() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

 private:
  QScopedPointer<QLineEdit> m_widget;
};

#endif  // STRING_NODE_VALUE_ITEM_H
