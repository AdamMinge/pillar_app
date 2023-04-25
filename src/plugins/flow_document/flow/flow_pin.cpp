/* ----------------------------------- Local -------------------------------- */
#include "flow_document/flow/flow_pin.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

FlowPin::FlowPin(QVariant data, QString caption)
    : m_data(std::move(data)), m_caption(std::move(caption)) {}

FlowPin::~FlowPin() = default;

const QVariant &FlowPin::getData() const { return m_data; }

const QString &FlowPin::getCaption() const { return m_caption; }

void FlowPin::setData(QVariant data) {
  m_data = std::move(data);
  dataChangeNotify();
}

void FlowPin::setCaption(QString caption) { m_caption = caption; }

void FlowPin::addListener(Listener &&listener) {
  m_listeners.push_back(std::move(listener));
}

void FlowPin::clearListeners() { m_listeners.clear(); }

void FlowPin::dataChangeNotify() {
  for (auto &listener : m_listeners) listener(m_data);
}

}  // namespace flow_document
