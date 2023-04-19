#ifndef FLOW_GROUP_COMMAND_H
#define FLOW_GROUP_COMMAND_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/command/command.h"
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class LIB_FLOW_API GroupCommand : public Command {
 public:
  explicit GroupCommand(QString name, Command *parent = nullptr);
  ~GroupCommand() override;

  void undo() override;
  void redo() override;

  [[nodiscard]] bool canMergeWith(const Command &other) const override;
  void mergeWith(const Command &other) override;

  void addCommand(Command *command);
  void removeCommand(Command *command);
  [[nodiscard]] const QList<Command *> &getCommands() const;

 private:
  QList<Command *> m_commands;
};

}  // namespace flow

#endif  // FLOW_GROUP_COMMAND_H
