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

  auto document_type = static_cast<api::IDocument::Type>(index.row());
  switch (role)// NOLINT(hicpp-multiway-paths-covered)
  {
    case Role::DocumentTypeRole:
      return QVariant::fromValue(document_type);

    case Role::DocumentTypeNameRole:
      return getDocumentNameForType(document_type);

    case Role::DocumentTypeIconRole:
      return getDocumentIconForType(document_type);
  }

  return QVariant{};
}

int DocumentTypeListModel::rowCount(const QModelIndex &parent) const
{
  return static_cast<int>(api::IDocument::Type::Unknown);
}

QString DocumentTypeListModel::getDocumentNameForType(api::IDocument::Type type)
{
  switch (type)
  {
    case api::IDocument::Type::Flow:
      return tr("Flow");

    case api::IDocument::Type::Unknown:
    default:
      return tr("Unknown");
  }
}

QIcon DocumentTypeListModel::getDocumentIconForType(api::IDocument::Type type)
{
  switch (type)
  {
    case api::IDocument::Type::Flow:
      return QIcon(":/images/64x64/flow_document.png");

    case api::IDocument::Type::Unknown:
    default:
      return QIcon(":/images/64x64/unknown_document.png");
  }
}
