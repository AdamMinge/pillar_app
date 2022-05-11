/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/node/pin.h"
#include "flow/libflow/node/node_data.h"
/* -------------------------------------------------------------------------- */

namespace flow::node
{

  Pin::Pin(std::unique_ptr<NodeData> data, QString caption)
      : m_data(std::move(data)), m_caption(std::move(caption))
  {}

  Pin::~Pin() = default;

  const NodeData &Pin::getData() const { return *m_data; }

  QString Pin::getCaption() const { return m_caption; }

  void Pin::setData(const NodeData &data) { m_data->assign(data); }

  void Pin::setCaption(const QString &caption) { m_caption = caption; }

  void Pin::addListener(Listener &&listener)
  {
    m_listeners.push_back(std::move(listener));
  }

  void Pin::clearListeners() { m_listeners.clear(); }

  void Pin::dataChanged(const NodeData &data)
  {
    for (auto &listener : m_listeners) listener(data);
  }

}// namespace flow::node