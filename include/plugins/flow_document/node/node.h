#ifndef FLOW_DOCUMENT_NODE_H
#define FLOW_DOCUMENT_NODE_H

/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/node/object.h"
#include "flow_document/node/pin.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FLOW_DOCUMENT_API Node : public Object {
 public:
  explicit Node();
  ~Node() override;

  [[nodiscard]] unsigned getPinsCounts(Pin::Type type) const;

  [[nodiscard]] const Pin &getPin(Pin::Type type, unsigned index) const;
  [[nodiscard]] Pin &getPin(Pin::Type type, unsigned index);

  void insertPin(Pin::Type type, Pin pin, int index);
  void removePin(Pin::Type type, int index);

 protected:
  virtual void compute() = 0;

 private:
  [[nodiscard]] std::vector<Pin> &getPins(Pin::Type type);
  [[nodiscard]] const std::vector<Pin> &getPins(Pin::Type type) const;

 private:
  std::vector<Pin> m_out_pins;
  std::vector<Pin> m_in_pins;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_NODE_H
