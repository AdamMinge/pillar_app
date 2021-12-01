/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "flow/tools/editor/document/document_type_list_model.h"
/* -------------------------------------------------------------------------- */

DocumentTypeListModel::DocumentTypeListModel(QObject* parent) :
  QAbstractListModel(parent)
{

}

DocumentTypeListModel::~DocumentTypeListModel() = default;

QVariant DocumentTypeListModel::data(const QModelIndex &index, int role) const
{
  if(index.row() < 0 || index.row() > rowCount(QModelIndex{}))
    return QVariant{};

  auto document_type = static_cast<Document::Type>(index.row());
  switch(role) // NOLINT(hicpp-multiway-paths-covered)
  {
    case Role::DocumentTypeRole:
      return QVariant::fromValue(document_type);

    case Role::DocumentTypeNameRole:
      return Document::getDocumentDisplayType(document_type);

    case Role::DocumentTypeIconRole:
      return Document::getDocumentIcon(document_type);
  }

  return QVariant{};
}

int DocumentTypeListModel::rowCount(const QModelIndex &parent) const
{
  return static_cast<int>(Document::Type::Unknown);
}
