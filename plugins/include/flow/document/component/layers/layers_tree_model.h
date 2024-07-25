#ifndef FLOW_DOCUMENT_LAYERS_TREE_MODEL_H
#define FLOW_DOCUMENT_LAYERS_TREE_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemModel>
#include <QIcon>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class FlowDocument;
class ChangeEvent;
class Layer;
class Flow;

class LIB_FLOW_DOCUMENT_API LayersTreeModel : public QAbstractItemModel {
  Q_OBJECT

 public:
  enum Column { NameColumn, VisibleColumn, LockedColumn };

 public:
  explicit LayersTreeModel(QObject *parent = nullptr);
  ~LayersTreeModel() override;

  void setDocument(FlowDocument *flow_document);
  [[nodiscard]] FlowDocument *getDocument() const;

  [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

  [[nodiscard]] QVariant data(const QModelIndex &index,
                              int role) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role);

  [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation,
                                    int role) const override;

  [[nodiscard]] QModelIndex index(Layer *layer, int column = 0) const;
  [[nodiscard]] QModelIndex index(int row, int column,
                                  const QModelIndex &parent) const override;
  [[nodiscard]] QModelIndex parent(const QModelIndex &index) const override;

  [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
  [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

  [[nodiscard]] QStringList mimeTypes() const override;
  [[nodiscard]] QMimeData *mimeData(
      const QModelIndexList &indexes) const override;
  [[nodiscard]] Qt::DropActions supportedDropActions() const override;
  [[nodiscard]] bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                                  int row, int column,
                                  const QModelIndex &parent) override;

  [[nodiscard]] Layer *toLayer(const QModelIndex &index) const;

 private:
  void onEvent(const ChangeEvent &event);

  [[nodiscard]] QString getName(const QModelIndex &index) const;
  [[nodiscard]] QIcon getIcon(const QModelIndex &index) const;
  [[nodiscard]] Qt::CheckState isVisible(const QModelIndex &index) const;
  [[nodiscard]] Qt::CheckState isLocked(const QModelIndex &index) const;

  void setName(const QModelIndex &index, const QString &name);
  void setVisible(const QModelIndex &index, Qt::CheckState state);
  void setLocked(const QModelIndex &index, Qt::CheckState state);

 private:
  FlowDocument *m_document;
  Flow *m_flow;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_LAYERS_TREE_MODEL_H
