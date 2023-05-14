#ifndef FLOW_DOCUMENT_FLOW_DOCUMENT_H
#define FLOW_DOCUMENT_FLOW_DOCUMENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QList>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/document/document.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/layer.h"
#include "flow_document/flow/object.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class ChangeEvent;
class Flow;

class FLOW_DOCUMENT_API FlowDocument : public egnite::Document {
  Q_OBJECT

 public:
  static std::unique_ptr<egnite::Document> create();

 public:
  ~FlowDocument() override;

  [[nodiscard]] Flow *getFlow() const;

  [[nodiscard]] Layer *getCurrentLayer() const;

  [[nodiscard]] const QList<Layer *> &getSelectedLayers() const;
  [[nodiscard]] const QList<Object *> &getSelectedObject() const;

 public Q_SLOTS:
  void setCurrentLayer(Layer *layer);

  void setSelectedLayers(const QList<Layer *> &layers);
  void setSelectedObjects(const QList<Object *> &objects);

 Q_SIGNALS:
  void event(const ChangeEvent &event);

  void currentLayerChanged(Layer *layer);

  void selectedLayersChanged(const QList<Layer *> &layers);
  void selectedObjectsChanged(const QList<Object *> &objects);

 protected:
  explicit FlowDocument(QObject *parent = nullptr);

 private:
  std::unique_ptr<Flow> m_flow;

  Layer *m_current_layer;

  QList<Layer *> m_selected_layers;
  QList<Object *> m_selected_objects;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_DOCUMENT_H
