#ifndef FLOW_DOCUMENT_DUPLICATE_LAYER_H
#define FLOW_DOCUMENT_DUPLICATE_LAYER_H

/* ----------------------------------- Egnite ------------------------------- */
#include <egnite/command/command.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class GroupLayer;
class Layer;

/* ------------------------------- DuplicateData ---------------------------- */

struct DuplicateData {
 public:
  explicit DuplicateData(DuplicateData&& other);
  explicit DuplicateData(Layer* layer);
  ~DuplicateData();

 public:
  GroupLayer* group_layer;
  std::unique_ptr<Layer> copy_layer;
  qsizetype index;
};

/* ------------------------------ DuplicateLayers --------------------------- */

class FLOW_DOCUMENT_API DuplicateLayers : public egnite::Command {
 public:
  explicit DuplicateLayers(FlowDocument* document, QList<Layer*> layers,
                           Command* parent = nullptr);
  ~DuplicateLayers() override;

  void undo() override;
  void redo() override;

 protected:
  FlowDocument* m_document;
  std::list<DuplicateData> m_duplicate_data;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_DUPLICATE_LAYER_H