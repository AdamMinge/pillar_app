/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/document_type_list_model.h"
/* -------------------------------------------------------------------------- */

DocumentTypeListModel::DocumentTypeListModel(QObject *parent)
    : QAbstractListModel(parent)
{}

DocumentTypeListModel::~DocumentTypeListModel() = default;

QVariant DocumentTypeListModel::data(const QModelIndex &index, int role) const
{
  if (index.row() < 0 || index.row() > rowCount(QModelIndex{}))
    return QVariant{};

  switch (role)// NOLINT(hicpp-multiway-paths-covered)
  {
    case Role::DocumentTypeIdRole:
      return QString{};

    case Qt::DisplayRole:
    case Role::DocumentTypeNameRole:
      return QString{};

    case Qt::DecorationRole:
    case Role::DocumentTypeIconRole:
      return QIcon{};
  }

  return QVariant{};
}

int DocumentTypeListModel::rowCount(const QModelIndex &parent) const
{
  return 0;
}
