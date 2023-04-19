#ifndef FLOW_COMMAND_H
#define FLOW_COMMAND_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QUndoCommand>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_API Command : public QUndoCommand {
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

}  // namespace flow

#endif  // FLOW_COMMAND_H
