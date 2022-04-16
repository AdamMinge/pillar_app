/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/pin.h"
#include "flow/modules/node/data/node_data.h"
/* -------------------------------------------------------------------------- */

namespace node
{

  Pin::Pin(std::unique_ptr<data::NodeData> data, Policy policy, QString caption)
      : m_data(std::move(data)), m_policy(policy), m_caption(std::move(caption))
  {}

  Pin::~Pin() = default;

  const data::NodeData &Pin::getData() const { return *m_data; }

  void Pin::setCaption(const QString &caption)
  {
    m_caption = caption;
    Q_EMIT captionChanged(m_caption);
  }

  void Pin::setData(const data::NodeData &data)
  {
    Q_ASSERT(
      m_data->staticMetaObject.className() ==
      data.staticMetaObject.className());

    m_data->assign(data);
    Q_EMIT dataChanged(*m_data);
  }

  void Pin::setPolicy(Pin::Policy policy)
  {
    m_policy = policy;
    Q_EMIT policyChanged(m_policy);
  }

}// namespace node