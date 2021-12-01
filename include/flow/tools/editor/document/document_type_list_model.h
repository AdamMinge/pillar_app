#ifndef FLOW_DOCUMENT_TYPE_LIST_MODEL_H
#define FLOW_DOCUMENT_TYPE_LIST_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractListModel>
#include <QStringList>
#include <QIcon>
/* ----------------------------------- Local -------------------------------- */
#include "flow/tools/editor/document/document.h"
/* -------------------------------------------------------------------------- */

class DocumentTypeListModel : public QAbstractListModel
{
  Q_OBJECT

public:
  enum Role
  {
    DocumentTypeRole = Qt::UserRole + 1,
    DocumentTypeNameRole,
    DocumentTypeIconRole,
  };

public:
  explicit DocumentTypeListModel(QObject* parent = nullptr);
  ~DocumentTypeListModel() override;

  [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
  [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
};

#endif //FLOW_DOCUMENT_TYPE_LIST_MODEL_H
