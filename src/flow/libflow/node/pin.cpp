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

  void Pin::setCaption(const QString &caption)
  {
    m_caption = caption;
    Q_EMIT captionChanged(m_caption);
  }

  void Pin::setData(const NodeData &data)
  {
    m_data->assign(data);
    Q_EMIT dataChanged(*m_data);
  }

}// namespace flow::node