/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/object.h"
/* -------------------------------------------------------------------------- */

namespace flow
{
  Object::Object() = default;

  Object::~Object() = default;

  void Object::setPosition(const QPointF &position)
  {
    if (m_position == position) return;

    m_position = position;
    Q_EMIT positionChanged(position);
  }

  QPointF Object::getPosition() const { return m_position; }
}// namespace flow
