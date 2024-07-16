#ifndef FLOW_DOCUMENT_LAYER_ITERATOR_H
#define FLOW_DOCUMENT_LAYER_ITERATOR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QStack>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

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

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYER_ITERATOR_H