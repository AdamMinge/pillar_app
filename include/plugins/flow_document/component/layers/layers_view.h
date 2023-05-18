#ifndef FLOW_DOCUMENT_LAYERS_VIEW_H
#define FLOW_DOCUMENT_LAYERS_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QTreeView>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;

class FLOW_DOCUMENT_API LayersView : public QTreeView {
  Q_OBJECT

 public:
  explicit LayersView(QWidget *parent = nullptr);
  ~LayersView() override;

  void setDocument(FlowDocument *document);
  [[nodiscard]] FlowDocument *getDocument() const;

 private Q_SLOTS:
  void selectionChanged();

 private:
  FlowDocument *m_document;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYERS_VIEW_H
