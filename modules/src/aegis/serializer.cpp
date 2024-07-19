/* ----------------------------------- Local -------------------------------- */
#include "aegis/serializer.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

Serializer::Serializer(Format format) : m_format(format) {}

Serializer::~Serializer() = default;

}  // namespace aegis
