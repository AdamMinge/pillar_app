/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/object.h"
/* -------------------------------------------------------------------------- */

namespace flow
{

  Object::Object() = default;

  Object::~Object() = default;

  void Object::setPosition(const QPointF &position) { m_position = position; }

  QPointF Object::getPosition() const { return m_position; }

  void Object::setProperties(const QVariantMap &properties)
  {
    m_properties = properties;
  }

  const QVariantMap &Object::getProperties() const { return m_properties; }

}// namespace flow
