#ifndef FLOW_DOCUMENT_LAYER_ITERATOR_H
#define FLOW_DOCUMENT_LAYER_ITERATOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QStack>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class Layer;

/* --------------------------- LayerPostOrderIterator ----------------------- */

class LayerPostOrderIterator {
 public:
  explicit LayerPostOrderIterator(Layer* root);
  ~LayerPostOrderIterator();

  [[nodiscard]] bool hasNext() const;
  [[nodiscard]] Layer* next();

 private:
  QStack<Layer*> m_stack;
};

/* --------------------------- LayerPreOrderIterator ------------------------ */

class LayerPreOrderIterator {
 public:
  explicit LayerPreOrderIterator(Layer* root);
  ~LayerPreOrderIterator();

  [[nodiscard]] bool hasNext() const;
  [[nodiscard]] Layer* next();

 private:
  QStack<Layer*> m_stack;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_LAYER_ITERATOR_H