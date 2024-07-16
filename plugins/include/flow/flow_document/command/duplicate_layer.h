#ifndef FLOW_DOCUMENT_DUPLICATE_LAYER_H
#define FLOW_DOCUMENT_DUPLICATE_LAYER_H

/* ----------------------------------- Pillar ------------------------------- */
#include <pillar/command/command.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class GroupLayer;
class Layer;

/* ---------------------------- DuplicateLayerData -------------------------- */

struct DuplicateLayerData {
 public:
  explicit DuplicateLayerData(DuplicateLayerData&& other);
  explicit DuplicateLayerData(Layer* layer);
  ~DuplicateLayerData();

 public:
  GroupLayer* group_layer;
  std::unique_ptr<Layer> copy_layer;
  qsizetype index;
};

/* ------------------------------ DuplicateLayers --------------------------- */

class FLOW_DOCUMENT_API DuplicateLayers : public pillar::Command {
 public:
  explicit DuplicateLayers(FlowDocument* document, QList<Layer*> layers,
                           Command* parent = nullptr);
  ~DuplicateLayers() override;

  void undo() override;
  void redo() override;

 protected:
  FlowDocument* m_document;
  std::list<DuplicateLayerData> m_duplicate_data;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_DUPLICATE_LAYER_H