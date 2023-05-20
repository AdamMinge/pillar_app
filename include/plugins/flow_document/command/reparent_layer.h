#ifndef FLOW_DOCUMENT_REPARENT_LAYER_H
#define FLOW_DOCUMENT_REPARENT_LAYER_H

/* ----------------------------------- Egnite ------------------------------- */
#include <egnite/command/command.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class GroupLayer;
class Layer;

class FLOW_DOCUMENT_API ReparentLayers : public egnite::Command {
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
  void reparent();

 private:
  FlowDocument* m_document;
  std::list<ReparentData> m_reparent_data;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_REPARENT_LAYER_H
