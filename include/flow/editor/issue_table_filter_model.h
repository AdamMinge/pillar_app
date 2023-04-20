#ifndef FLOW_ISSUE_TABLE_FILTER_MODEL_H
#define FLOW_ISSUE_TABLE_FILTER_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QSortFilterProxyModel>
/* -------------------------------------------------------------------------- */

class IssueTableFilterModel : public QSortFilterProxyModel {
  Q_OBJECT

 public:
  explicit IssueTableFilterModel(QObject *parent = nullptr);
  ~IssueTableFilterModel() override;

  [[nodiscard]] bool areWarningsVisible() const;
  [[nodiscard]] bool areErrorsVisible() const;

 public Q_SLOTS:
  void setWarningsVisible(bool visible = true);
  void setErrorsVisible(bool visible = true);

 protected:
  [[nodiscard]] bool filterAcceptsRow(
      int sourceRow, const QModelIndex &sourceParent) const override;

 private:
  bool m_warnings_visible;
  bool m_errors_visible;
};

#endif  // FLOW_ISSUE_TABLE_FILTER_MODEL_H
