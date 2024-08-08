/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/sniffer.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

Sniffer::Sniffer(QObject *parent) : QObject(parent), m_last_object(nullptr) {}

Sniffer::~Sniffer() = default;

bool Sniffer::eventFilter(QObject *object, QEvent *event) {
  if (m_last_object != object) {
    m_last_object = object;
  }

  return QObject::eventFilter(object, event);
}

}  // namespace aegis
