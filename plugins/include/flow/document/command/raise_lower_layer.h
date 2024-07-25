#ifndef FLOW_DOCUMENT_RAISE_LOWER_LAYER_H
#define FLOW_DOCUMENT_RAISE_LOWER_LAYER_H

/* ----------------------------------- Pillar ------------------------------- */
#include <pillar/command/command.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class FlowDocument;
class GroupLayer;
class Layer;

/* ----------------------------- RaiseLowerLayers --------------------------- */

class LIB_FLOW_DOCUMENT_API RaiseLowerLayers : public pillar::Command {
 public:
  explicit RaiseLowerLayers(const QString& name, FlowDocument* document,
                            QList<Layer*> layers, Command* parent = nullptr);
  ~RaiseLowerLayers() override;

 protected:
  void raiseLayers();
  void lowerLayers();

 private:
  void moveLayers(bool raise);
  void moveLayer(Layer* layer, GroupLayer* parent, qsizetype index);

 protected:
  FlowDocument* m_document;
  QList<Layer*> m_layers;
};

/* -------------------------------- RaiseLayers ----------------------------- */

class LIB_FLOW_DOCUMENT_API RaiseLayers : public RaiseLowerLayers {
 public:
  explicit RaiseLayers(FlowDocument* document, QList<Layer*> layers,
                       Command* parent = nullptr);
  ~RaiseLayers() override;

  void undo() override;
  void redo() override;
};

/* -------------------------------- LowerLayers ----------------------------- */

class LIB_FLOW_DOCUMENT_API LowerLayers : public RaiseLowerLayers {
 public:
  explicit LowerLayers(FlowDocument* document, QList<Layer*> layers,
                       Command* parent = nullptr);
  ~LowerLayers() override;

  void undo() override;
  void redo() override;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_RAISE_LOWER_LAYER_H
