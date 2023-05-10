#ifndef FLOW_DOCUMENT_LAYERS_DOCK_H
#define FLOW_DOCUMENT_LAYERS_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QSortFilterProxyModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui {
class LayersDock;
}

namespace flow_document {

class LayersTreeModel;

class FLOW_DOCUMENT_API LayersDock : public QDockWidget {
  Q_OBJECT

 public:
  explicit LayersDock(QWidget *parent = nullptr);
  ~LayersDock() override;

 protected:
  void changeEvent(QEvent *event) override;

 private Q_SLOTS:
  void searchLayers(const QString &search);

 private:
  void initUi();
  void initConnections();

  void retranslateUi();

 private:
  QScopedPointer<Ui::LayersDock> m_ui;

  QScopedPointer<LayersTreeModel> m_layers_model;
  QScopedPointer<QSortFilterProxyModel> m_search_proxy_model;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_LAYERS_DOCK_H
