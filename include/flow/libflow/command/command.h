#ifndef FLOW_COMMAND_H
#define FLOW_COMMAND_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QUndoCommand>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow::command
{

  class LIB_FLOW_API Command : public QUndoCommand
  {
  public:
    explicit Command(Command *parent = nullptr);
    ~Command() override;

    bool mergeWith(const QUndoCommand *other) override;

    [[nodiscard]] virtual bool canMergeWith(const Command &other) const;
    virtual void mergeWith(const Command &other);
  };

}// namespace flow::command


#endif//FLOW_COMMAND_H
