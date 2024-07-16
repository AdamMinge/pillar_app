#ifndef PILLAR_COMMAND_H
#define PILLAR_COMMAND_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QUndoCommand>
/* ----------------------------------- Local -------------------------------- */
#include "pillar/export.h"
/* -------------------------------------------------------------------------- */

namespace pillar {

class LIB_PILLAR_API Command : public QUndoCommand {
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

}  // namespace pillar

#endif  // PILLAR_COMMAND_H
