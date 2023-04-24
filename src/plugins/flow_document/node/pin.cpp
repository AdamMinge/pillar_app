/* ----------------------------------- Local -------------------------------- */
#include "flow_document/node/pin.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

Pin::Pin(QVariant data, QString caption)
    : m_data(std::move(data)), m_caption(std::move(caption)) {}

Pin::~Pin() = default;

const QVariant &Pin::getData() const { return m_data; }

const QString &Pin::getCaption() const { return m_caption; }

void Pin::setData(QVariant data) {
  m_data = std::move(data);
  dataChangeNotify();
}

void Pin::setCaption(QString caption) { m_caption = caption; }

void Pin::addListener(Listener &&listener) {
  m_listeners.push_back(std::move(listener));
}

void Pin::clearListeners() { m_listeners.clear(); }

void Pin::dataChangeNotify() {
  for (auto &listener : m_listeners) listener(m_data);
}

}  // namespace flow_document
