#ifndef FLOW_DOCUMENT_ADD_REMOVE_LAYER_H
#define FLOW_DOCUMENT_ADD_REMOVE_LAYER_H

/* ---------------------------------- Standard ------------------------------ */
#include <list>
#include <memory>
/* ----------------------------------- Pillar ------------------------------- */
#include <pillar/command/command.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class FlowDocument;
class GroupLayer;
class Layer;

/* --------------------------------- LayerEntry ----------------------------- */

struct LIB_FLOW_DOCUMENT_API LayerEntry {
 public:
  explicit LayerEntry(LayerEntry&& other);
  explicit LayerEntry(GroupLayer* group_layer, qsizetype index);
  explicit LayerEntry(GroupLayer* group_layer, std::unique_ptr<Layer> new_layer,
                      qsizetype index);
  ~LayerEntry();

 public:
  GroupLayer* group_layer;
  std::unique_ptr<Layer> new_layer;
  qsizetype index;
};

/* ------------------------------ AddRemoveLayers --------------------------- */

class LIB_FLOW_DOCUMENT_API AddRemoveLayers : public pillar::Command {
 public:
  explicit AddRemoveLayers(const QString& name, FlowDocument* document,
                           std::list<LayerEntry> entries,
                           Command* parent = nullptr);
  ~AddRemoveLayers() override;

 protected:
  void addLayer();
  void removeLayer();

 protected:
  FlowDocument* m_document;
  std::list<LayerEntry> m_entries;
};

/* ---------------------------------- AddLayers ----------------------------- */

class LIB_FLOW_DOCUMENT_API AddLayers : public AddRemoveLayers {
 public:
  explicit AddLayers(FlowDocument* document, std::list<LayerEntry> entries,
                     Command* parent = nullptr);
  ~AddLayers() override;

  void undo() override;
  void redo() override;
};

/* -------------------------------- RemoveLayers ---------------------------- */

class LIB_FLOW_DOCUMENT_API RemoveLayers : public AddRemoveLayers {
 public:
  RemoveLayers(FlowDocument* document, std::list<LayerEntry> entries,
               Command* parent = nullptr);
  ~RemoveLayers() override;

  void undo() override;
  void redo() override;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_ADD_REMOVE_LAYER_H