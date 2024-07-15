#ifndef EGNITE_COMMAND_H
#define EGNITE_COMMAND_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QUndoCommand>
/* ----------------------------------- Local -------------------------------- */
#include "egnite/export.h"
/* -------------------------------------------------------------------------- */

namespace egnite {

class LIB_EGNITE_API Command : public QUndoCommand {
 public:
  explicit Command(QString name, Command *parent = nullptr);
  ~Command() override;

  bool mergeWith(const QUndoCommand *other) override;

  [[nodiscard]] virtual bool canMergeWith(const Command &other) const;
  virtual void mergeWith(const Command &other);

  [[nodiscard]] int id() const override;
  [[nodiscard]] QString name() const;

 private:
  QString m_name;
};

}  // namespace egnite

#endif  // EGNITE_COMMAND_H
