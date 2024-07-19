/* ----------------------------------- Local -------------------------------- */
#include "aegis/command/command.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

Command::Command(const Serializer& serializer) : m_serializer(serializer) {}

Command::~Command() = default;

}  // namespace aegis
