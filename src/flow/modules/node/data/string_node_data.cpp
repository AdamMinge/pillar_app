/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/data/string_node_data.h"
/* -------------------------------------------------------------------------- */

namespace node::data
{

  StringNodeData::StringNodeData(QString value) : m_value(value) {}

  StringNodeData::~StringNodeData() = default;

  void StringNodeData::setValue(QString value) { m_value = value; }

  QString StringNodeData::getValue() const { return m_value; }

  void StringNodeData::assign(const NodeData &data)
  {
    auto &string_node_data = dynamic_cast<const StringNodeData &>(data);
    setValue(string_node_data.getValue());
  }

}// namespace node::data
