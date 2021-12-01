/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "flow/tools/editor/document/document_list_model.h"
#include "flow/tools/editor/preferences_manager.h"
/* -------------------------------------------------------------------------- */

DocumentListModel::DocumentListModel(QObject* parent) :
  QAbstractListModel(parent)
{
  connect(std::addressof(PreferencesManager::getInstance()), &PreferencesManager::recentDocumentFilesChanged,
          this, &DocumentListModel::recentProjectFilesChanged);

  recentProjectFilesChanged();
}

DocumentListModel::~DocumentListModel() = default;

QVariant DocumentListModel::data(const QModelIndex &index, int role) const
{
  if(index.row() < 0 || index.row() >= rowCount(QModelIndex{}))
    return QVariant{};

  switch(role) // NOLINT(hicpp-multiway-paths-covered)
  {
    case Role::DocumentNameRole:
      return QFileInfo(m_documents.at(index.row())).baseName();

    case Role::DocumentPathRole:
      return m_documents.at(index.row());

    case Role::DocumentIconRole:
      return getDocumentIcon(index);

    case Role::DocumentLastModifiedDateRole:
      return QFileInfo(m_documents.at(index.row())).lastModified();
  }

  return QVariant{};
}

int DocumentListModel::rowCount(const QModelIndex &parent) const
{
  return static_cast<int>(m_documents.size());
}

void DocumentListModel::recentProjectFilesChanged()
{
  beginResetModel();
  m_documents = PreferencesManager::getInstance().getRecentDocumentFiles();
  endResetModel();
}

QIcon DocumentListModel::getDocumentIcon(const QModelIndex& index) const
{
  const auto document_file_name = m_documents.at(index.row());

  auto document_type = Document::Type::Unknown;
  for(auto type_id = static_cast<int>(Document::Type::Flow);
           type_id < static_cast<int>(Document::Type::Unknown); ++type_id)
  {
    const auto extension = Document::getDocumentExtension(static_cast<Document::Type>(type_id));
    if(document_file_name.endsWith(extension))
      document_type = static_cast<Document::Type>(type_id);
  }

  return Document::getDocumentIcon(document_type);
}
