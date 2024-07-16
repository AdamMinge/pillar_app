#ifndef ISSUE_TABLE_MODEL_H
#define ISSUE_TABLE_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractTableModel>
#include <QIcon>
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/issue.h>
/* -------------------------------------------------------------------------- */

class IssueTableModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  enum Role {
    IssueRole = Qt::UserRole + 1,
  };

  enum Column { SeverityColumn, DescriptionColumn, OccurrencesColumn };

 public:
  explicit IssueTableModel(QObject *parent = nullptr);
  ~IssueTableModel() override;

  [[nodiscard]] QVariant data(const QModelIndex &index,
                              int role) const override;

  [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
  [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

  [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation,
                                    int role) const override;

 public Q_SLOTS:
  void addIssue(const pillar::Issue &issue);

  void removeIssues(const QVariant &context);
  void removeAllIssues();

 private:
  [[nodiscard]] QIcon getIssueIcon(const QModelIndex &index) const;
  [[nodiscard]] QString getIssueSeverityName(const QModelIndex &index) const;

 private:
  QVector<std::pair<pillar::Issue, unsigned>> m_issues;
};

#endif  // ISSUE_TABLE_MODEL_H
