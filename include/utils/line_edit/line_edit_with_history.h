#ifndef UTILS_LINE_EDIT_LINE_EDIT_WITH_HISTORY_H
#define UTILS_LINE_EDIT_LINE_EDIT_WITH_HISTORY_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QLineEdit>
#include <QStringList>
/* ----------------------------------- Local -------------------------------- */
#include "utils/line_edit/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

class LINE_EDIT_API QtLineEditWithHistory : public QLineEdit {
  Q_OBJECT

 public:
  explicit QtLineEditWithHistory(QWidget *parent = nullptr);
  ~QtLineEditWithHistory() override;

 public Q_SLOTS:
  void appendToHistory(QString text);

  void setHistory(QStringList history);
  [[nodiscard]] QStringList getHistory() const;

  void move(qsizetype direction);
  void moveNext();
  void movePrev();

 private:
  QStringList m_history;
  qsizetype m_history_position;
};

}  // namespace utils

#endif  // UTILS_LINE_EDIT_LINE_EDIT_WITH_HISTORY_H
