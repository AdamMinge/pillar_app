#ifndef FLOW_DOCUMENT_LIST_MODEL_H
#define FLOW_DOCUMENT_LIST_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractListModel>
#include <QStringList>
#include <QIcon>
/* ----------------------------------- Local -------------------------------- */
#include "flow/tools/editor/document/document.h"
/* -------------------------------------------------------------------------- */

class DocumentListModel : public QAbstractListModel
{
  Q_OBJECT

public:
  enum Role
  {
    DocumentNameRole = Qt::UserRole + 1,
    DocumentPathRole,
    DocumentIconRole,
    DocumentLastModifiedDateRole,
  };

public:
  explicit DocumentListModel(QObject* parent = nullptr);
  ~DocumentListModel() override;

  [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
  [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

private:
  [[nodiscard]] QIcon getDocumentIcon(const QModelIndex& index) const;

private Q_SLOTS:
  void recentProjectFilesChanged();

private:
  QStringList m_documents;
};

#endif //FLOW_DOCUMENT_LIST_MODEL_H
