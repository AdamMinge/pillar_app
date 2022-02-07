/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/logic/logic_node_data.h"
/* -------------------------------------------------------------------------- */

namespace plugins::node::logic
{

  LogicNodeData::LogicNodeData(bool value) : m_value(value) {}

  LogicNodeData::~LogicNodeData() = default;

  void LogicNodeData::setValue(bool value) { m_value = value; }

  bool LogicNodeData::getValue() const { return m_value; }

  QString LogicNodeData::getId() const { return QLatin1String("LogicData"); }

  QString LogicNodeData::getName() const { return QLatin1String("Logic Data"); }

}// namespace plugins::node::logic