#ifndef FLOW_DOCUMENT_CHANGE_LAYER_H
#define FLOW_DOCUMENT_CHANGE_LAYER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/command/change_value.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class Layer;

/* ------------------------------ SetLayersVisible -------------------------- */

class FLOW_DOCUMENT_API SetLayersVisible : public ChangeValue<Layer, bool> {
 public:
  explicit SetLayersVisible(FlowDocument* document, QList<Layer*> layers,
                            bool visible, Command* parent = nullptr);
  ~SetLayersVisible() override;

 protected:
  [[nodiscard]] bool getValue(const Layer* layer) const override;
  void setValue(Layer* layer, const bool& visible) override;
};

/* ------------------------------ SetLayersLocked --------------------------- */

class FLOW_DOCUMENT_API SetLayersLocked : public ChangeValue<Layer, bool> {
 public:
  explicit SetLayersLocked(FlowDocument* document, QList<Layer*> layers,
                           bool locked, Command* parent = nullptr);
  ~SetLayersLocked() override;

 protected:
  [[nodiscard]] bool getValue(const Layer* layer) const override;
  void setValue(Layer* layer, const bool& locked) override;
};

/* ------------------------------- SetLayersName ---------------------------- */

class FLOW_DOCUMENT_API SetLayersName : public ChangeValue<Layer, QString> {
 public:
  explicit SetLayersName(FlowDocument* document, QList<Layer*> layers,
                         QString name, Command* parent = nullptr);
  ~SetLayersName() override;

 protected:
  [[nodiscard]] QString getValue(const Layer* layer) const override;
  void setValue(Layer* layer, const QString& name) override;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_CHANGE_LAYER_H