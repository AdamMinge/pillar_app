/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/serializer.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

ResponseSerializer::ResponseSerializer(Format format) : m_format(format) {}

ResponseSerializer::~ResponseSerializer() = default;

}  // namespace aegis
