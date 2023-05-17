#ifndef FLOW_DOCUMENT_CHANGE_LAYER_H
#define FLOW_DOCUMENT_CHANGE_LAYER_H

/* ----------------------------------- Egnite ------------------------------- */
#include <egnite/command/command.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class Layer;

/* ------------------------------ SetLayersVisible -------------------------- */

class FLOW_DOCUMENT_API SetLayersVisible : public egnite::Command {
 public:
  explicit SetLayersVisible(FlowDocument* document, QList<Layer*> layers,
                            bool visible, Command* parent = nullptr);
  ~SetLayersVisible() override;

  void undo() override;
  void redo() override;

 private:
  void setVisible(bool visible);

 protected:
  FlowDocument* m_document;
  QList<Layer*> m_layers;
  bool m_visible;
};

/* ------------------------------ SetLayersLocked --------------------------- */

class FLOW_DOCUMENT_API SetLayersLocked : public egnite::Command {
 public:
  explicit SetLayersLocked(FlowDocument* document, QList<Layer*> layers,
                           bool locked, Command* parent = nullptr);
  ~SetLayersLocked() override;

  void undo() override;
  void redo() override;

 private:
  void setLocked(bool locked);

 protected:
  FlowDocument* m_document;
  QList<Layer*> m_layers;
  bool m_locked;
};

/* ------------------------------- SetLayerName ----------------------------- */

class FLOW_DOCUMENT_API SetLayerName : public egnite::Command {
 public:
  explicit SetLayerName(FlowDocument* document, Layer* layer, QString name,
                        Command* parent = nullptr);
  ~SetLayerName() override;

  void undo() override;
  void redo() override;

 private:
  void setName();

 protected:
  FlowDocument* m_document;
  Layer* m_layer;
  QString m_name;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CHANGE_LAYER_H