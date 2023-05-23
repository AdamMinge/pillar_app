#ifndef UTILS_DELEGATE_CONDITIONAL_BOLD_DELEGATE_H
#define UTILS_DELEGATE_CONDITIONAL_BOLD_DELEGATE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QStyledItemDelegate>
/* --------------------------------- Standard ------------------------------- */
#include <functional>
/* ----------------------------------- Local -------------------------------- */
#include "utils/delegate/export.h"
/* -------------------------------------------------------------------------- */

namespace utils {

class QtConditionalBoldDelegate : public QStyledItemDelegate {
 public:
  using Condition = std::function<bool(const QModelIndex &)>;

 public:
  explicit QtConditionalBoldDelegate(Condition condition,
                                     QObject *parent = nullptr);
  ~QtConditionalBoldDelegate() override;

 protected:
  void initStyleOption(QStyleOptionViewItem *option,
                       const QModelIndex &index) const override;

 private:
  Condition m_condition;
};

}  // namespace utils

#endif  // UTILS_DELEGATE_CONDITIONAL_BOLD_DELEGATE_H
