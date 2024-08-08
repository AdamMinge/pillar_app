/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/command/command.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

Command::Command(const CommandExecutor& manager) : m_manager(manager) {}

Command::~Command() = default;

const CommandExecutor& Command::getManager() const { return m_manager; }

}  // namespace aegis
