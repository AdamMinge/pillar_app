/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/command/command.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

Command::Command(const CommandManager& manager) : m_manager(manager) {}

Command::~Command() = default;

const CommandManager& Command::getManager() const { return m_manager; }

}  // namespace aegis
