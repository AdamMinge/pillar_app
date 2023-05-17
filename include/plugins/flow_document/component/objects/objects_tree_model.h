#ifndef FLOW_DOCUMENT_OBJECTS_TREE_MODEL_H
#define FLOW_DOCUMENT_OBJECTS_TREE_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemModel>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class ChangeEvent;
class Object;
class Flow;

class FLOW_DOCUMENT_API ObjectsTreeModel : public QAbstractItemModel {
  Q_OBJECT

 public:
  enum Column { NameColumn };

 public:
  explicit ObjectsTreeModel(QObject *parent = nullptr);
  ~ObjectsTreeModel() override;

  void setDocument(FlowDocument *flow_document);
  [[nodiscard]] FlowDocument *getDocument() const;

  [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

  [[nodiscard]] QVariant data(const QModelIndex &index,
                              int role) const override;
  [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation,
                                    int role) const override;

  [[nodiscard]] QModelIndex index(int row, int column,
                                  const QModelIndex &parent) const override;
  [[nodiscard]] QModelIndex parent(const QModelIndex &index) const override;

  [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
  [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

 private:
  void onEvent(const ChangeEvent &event);

  [[nodiscard]] QString getName(const QModelIndex &index) const;
  [[nodiscard]] QIcon getIcon(const QModelIndex &index) const;

 private:
  FlowDocument *m_document;
  Flow *m_flow;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_OBJECTS_TREE_MODEL_H
