/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/command/command.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

Command::Command(const ResponseSerializer& serializer)
    : m_serializer(serializer) {}

Command::~Command() = default;

}  // namespace aegis
