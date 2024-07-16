#ifndef FLOW_DOCUMENT_LAYERS_DOCK_H
#define FLOW_DOCUMENT_LAYERS_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/flow_dock_widget.h"
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class LayersDock;
}

namespace flow_document {

class FlowDocument;
class LayersTreeModel;

class FLOW_DOCUMENT_API LayersDock : public FlowDockWidget {
  Q_OBJECT

 public:
  explicit LayersDock(QWidget *parent = nullptr);
  ~LayersDock() override;

 protected Q_SLOTS:
  void changeEvent(QEvent *event) override;
  void onDocumentChanged(FlowDocument *from, FlowDocument *to) override;

 private Q_SLOTS:
  void searchLayers(const QString &search);

 private:
  void initUi();
  void initConnections();

  void retranslateUi();

 private:
  QScopedPointer<Ui::LayersDock> m_ui;

  QScopedPointer<LayersTreeModel> m_layers_model;
  QScopedPointer<QSortFilterProxyModel> m_filter_model;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYERS_DOCK_H
