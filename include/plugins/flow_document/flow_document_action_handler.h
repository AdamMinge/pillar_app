#ifndef FLOW_DOCUMENT_FLOW_DOCUMENT_ACTION_HANDLER_H
#define FLOW_DOCUMENT_FLOW_DOCUMENT_ACTION_HANDLER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAction>
#include <QMenu>
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class ChangeEvent;
class Layer;
class Node;

class FLOW_DOCUMENT_API FlowDocumentActionHandler : public QObject {
  Q_OBJECT

 public:
  static FlowDocumentActionHandler& getInstance();
  static void deleteInstance();

 public:
  ~FlowDocumentActionHandler() override;

  void setDocument(FlowDocument* document);
  [[nodiscard]] FlowDocument* getDocument() const;

  [[nodiscard]] QAction* getAddGroupLayerAction() const;
  [[nodiscard]] QAction* getAddNodeLayerAction() const;
  [[nodiscard]] QAction* getRemoveLayerAction() const;
  [[nodiscard]] QAction* getRaiseLayerAction() const;
  [[nodiscard]] QAction* getLowerLayerAction() const;
  [[nodiscard]] QAction* getDuplicateLayerAction() const;
  [[nodiscard]] QAction* getShowHideOtherLayersAction() const;
  [[nodiscard]] QAction* getLockUnlockOtherLayersAction() const;

  [[nodiscard]] QAction* getRemoveNodeAction() const;
  [[nodiscard]] QAction* getRaiseNodeAction() const;
  [[nodiscard]] QAction* getLowerNodeAction() const;
  [[nodiscard]] QAction* getDuplicateNodeAction() const;

  [[nodiscard]] QMenu* createNewLayerMenu(QWidget* parent) const;

 private Q_SLOTS:
  void onAddGroupLayer() const;
  void onAddNodeLayer() const;
  void onRemoveLayer() const;
  void onRaiseLayer() const;
  void onLowerLayer() const;
  void onDuplicateLayer() const;
  void onShowHideOtherLayers() const;
  void onLockUnlockOtherLayers() const;

  void onRemoveNode() const;
  void onRaiseNode() const;
  void onLowerNode() const;
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

 private:
  static std::unique_ptr<FlowDocumentActionHandler> m_instance;

 private:
  FlowDocument* m_document;

  QAction* m_add_group_layer;
  QAction* m_add_node_layer;
  QAction* m_remove_layer;
  QAction* m_raise_layer;
  QAction* m_lower_layer;
  QAction* m_duplicate_layer;
  QAction* m_show_hide_other_layers;
  QAction* m_lock_unlock_other_layers;

  QAction* m_remove_node;
  QAction* m_raise_node;
  QAction* m_lower_node;
  QAction* m_duplicate_node;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_DOCUMENT_ACTION_HANDLER_H
