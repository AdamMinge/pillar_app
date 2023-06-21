#ifndef FLOW_DOCUMENT_FLOW_DOCUMENT_ACTION_HANDLER_H
#define FLOW_DOCUMENT_FLOW_DOCUMENT_ACTION_HANDLER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAction>
#include <QMenu>
#include <QObject>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_listener.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class ChangeEvent;
class ObjectFactory;
class Layer;
class Node;

class FLOW_DOCUMENT_API FlowDocumentActionHandler
    : public QObject,
      public egnite::PluginListener<ObjectFactory> {
  Q_OBJECT

 public:
  static FlowDocumentActionHandler& getInstance();
  static void deleteInstance();

 public:
  ~FlowDocumentActionHandler() override;

  void setDocument(FlowDocument* document);
  [[nodiscard]] FlowDocument* getDocument() const;

  [[nodiscard]] QMenu* getAddLayerMenu() const;
  [[nodiscard]] QAction* getRemoveLayerAction() const;
  [[nodiscard]] QAction* getRaiseLayerAction() const;
  [[nodiscard]] QAction* getLowerLayerAction() const;
  [[nodiscard]] QAction* getDuplicateLayerAction() const;
  [[nodiscard]] QAction* getShowHideOtherLayersAction() const;
  [[nodiscard]] QAction* getLockUnlockOtherLayersAction() const;

  [[nodiscard]] QMenu* getAddNodeMenu() const;
  [[nodiscard]] QAction* getRemoveNodeAction() const;
  [[nodiscard]] QAction* getMoveUpNodeAction() const;
  [[nodiscard]] QAction* getMoveDownNodeAction() const;
  [[nodiscard]] QAction* getDuplicateNodeAction() const;

 protected:
  void addedObject(ObjectFactory* factory) override;
  void removedObject(ObjectFactory* factory) override;

  [[nodiscard]] std::function<void()> methodForFactory(
      ObjectFactory* factory) const;
  [[nodiscard]] QMenu* menuForFactory(ObjectFactory* factory) const;

 private Q_SLOTS:
  void onRemoveLayer() const;
  void onRaiseLayer() const;
  void onLowerLayer() const;
  void onDuplicateLayer() const;
  void onShowHideOtherLayers() const;
  void onLockUnlockOtherLayers() const;

  void onRemoveNode() const;
  void onMoveUpNode() const;
  void onMoveDownNode() const;
  void onDuplicateNode() const;

  void onEvent(const ChangeEvent& event);

 private:
  explicit FlowDocumentActionHandler();

  void initActions();
  void connectActions();
  void updateActions();
  void retranslateUi();

  void registerActions();
  void unregisterActions();

  void addLayer(std::unique_ptr<Layer> layer) const;
  void addNode(std::unique_ptr<Node> node) const;

 private:
  static std::unique_ptr<FlowDocumentActionHandler> m_instance;

 private:
  FlowDocument* m_document;

  QScopedPointer<QMenu> m_add_layer_menu;
  QAction* m_remove_layer;
  QAction* m_raise_layer;
  QAction* m_lower_layer;
  QAction* m_duplicate_layer;
  QAction* m_show_hide_other_layers;
  QAction* m_lock_unlock_other_layers;

  QScopedPointer<QMenu> m_add_node_menu;
  QAction* m_remove_node;
  QAction* m_move_up_node;
  QAction* m_move_down_node;
  QAction* m_duplicate_node;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_DOCUMENT_ACTION_HANDLER_H
