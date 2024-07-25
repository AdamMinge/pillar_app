#ifndef FLOW_DOCUMENT_REPARENT_LAYER_H
#define FLOW_DOCUMENT_REPARENT_LAYER_H

/* ----------------------------------- Pillar ------------------------------- */
#include <pillar/command/command.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class FlowDocument;
class GroupLayer;
class Layer;

class LIB_FLOW_DOCUMENT_API ReparentLayers : public pillar::Command {
  struct ReparentData {
    Layer* layer;
    GroupLayer* parent;
    qsizetype index;
  };

 public:
  explicit ReparentLayers(FlowDocument* document, QVector<Layer*> layers,
                          GroupLayer* group_layer, qsizetype index,
                          Command* parent = nullptr);
  ~ReparentLayers() override;

  void undo() override;
  void redo() override;

 private:
  void reparentLayers(bool revert);
  void reparentLayer(ReparentData& data);

 private:
  FlowDocument* m_document;
  std::list<ReparentData> m_reparent_data;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_REPARENT_LAYER_H
