#ifndef FLOW_DOCUMENT_FLOW_DOCK_WIDGET_H
#define FLOW_DOCUMENT_FLOW_DOCK_WIDGET_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class FlowDocument;

class LIB_FLOW_DOCUMENT_API FlowDockWidget : public QDockWidget {
  Q_OBJECT

 public:
  explicit FlowDockWidget(QWidget *parent = nullptr);
  ~FlowDockWidget() override;

  void setDocument(FlowDocument *document);
  [[nodiscard]] FlowDocument *getDocument() const;

 protected Q_SLOTS:
  virtual void onDocumentChanged(FlowDocument *from, FlowDocument *to);

 private:
  FlowDocument *m_document;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_FLOW_DOCK_WIDGET_H
