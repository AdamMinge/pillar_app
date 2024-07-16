#ifndef FLOW_DOCUMENT_LAYERS_VIEW_H
#define FLOW_DOCUMENT_LAYERS_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QTreeView>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
#include "flow_document/flow/layer.h"
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

  void setModel(QAbstractItemModel *model) override;

 protected:
  void contextMenuEvent(QContextMenuEvent *event) override;
  void selectionChanged(const QItemSelection &selected,
                        const QItemSelection &deselected) override;
  [[nodiscard]] QItemSelectionModel::SelectionFlags selectionCommand(
      const QModelIndex &index, const QEvent *event = nullptr) const override;

 private Q_SLOTS:
  void onCurrentRowChanged(const QModelIndex &index);
  void onCurrentLayerChanged(Layer *layer);
  void onSelectedLayersChanged(const QList<Layer *> &layers);

  void onRowsInserted(const QModelIndex &parent, int first, int last);
  void onRowsRemoved(const QModelIndex &parent, int first, int last);

 private:
  FlowDocument *m_document;
  bool m_updating_selection;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYERS_VIEW_H
