#ifndef STRING_NODE_VALUE_ITEM_H
#define STRING_NODE_VALUE_ITEM_H

/* ------------------------------------- Qt --------------------------------- */
#include <QLineEdit>
#include <QScopedPointer>
/* ----------------------------- PluginFlowDocument ------------------------- */
#include <flow/document/component/scene/item/node_item.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/string_node/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class StringNodeStringEmittersChangeEvent;
class StringNodeStringEmitter;
class StringNodeStringReceiver;

/* ------------------------ StringNodeStringEmitterItem --------------------- */

class LIB_FLOW_STRING_NODE_API StringNodeStringEmitterItem : public NodeItem {
  Q_OBJECT

 public:
  explicit StringNodeStringEmitterItem(StringNodeStringEmitter *node,
                                       FlowDocument *document,
                                       QGraphicsItem *parent);
  ~StringNodeStringEmitterItem() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

 protected Q_SLOTS:
  void onEvent(const ChangeEvent &event) override;
  void onUpdate(const StringNodeStringEmittersChangeEvent &event);

 private:
  void apply();

 private:
  QScopedPointer<QLineEdit> m_widget;
  bool m_updating;
};

/* ------------------------ StringNodeStringReceiverItem -------------------- */

class LIB_FLOW_STRING_NODE_API StringNodeStringReceiverItem : public NodeItem {
  Q_OBJECT

 public:
  explicit StringNodeStringReceiverItem(StringNodeStringReceiver *node,
                                        FlowDocument *document,
                                        QGraphicsItem *parent);
  ~StringNodeStringReceiverItem() override;

  [[nodiscard]] QWidget *getEmbeddedWidget() const override;

 private:
  QScopedPointer<QLineEdit> m_widget;
};

}  // namespace flow

#endif  // STRING_NODE_VALUE_ITEM_H
