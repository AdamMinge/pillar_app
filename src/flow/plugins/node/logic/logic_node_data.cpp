/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/logic/logic_node_data.h"
/* -------------------------------------------------------------------------- */

namespace plugins::node::logic
{

  LogicNodeData::LogicNodeData(bool value) : m_value(value) {}

  LogicNodeData::~LogicNodeData() = default;

  void LogicNodeData::setValue(bool value) { m_value = value; }

  bool LogicNodeData::getValue() const { return m_value; }

  void LogicNodeData::assign(const NodeData &data)
  {
    auto &logic_node_data = dynamic_cast<const LogicNodeData &>(data);
    setValue(logic_node_data.getValue());
  }

  QString LogicNodeData::getName() const { return QObject::tr("Logic Data"); }

}// namespace plugins::node::logic