/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/scene/flow_style_manager.h"
#include "flow/plugins/document/flow/component/scene/flow_node_item.h"
/* -------------------------------------------------------------------------- */

QScopedPointer<FlowStyleManager> FlowStyleManager::m_instance =
  QScopedPointer<FlowStyleManager>(nullptr);

FlowStyleManager &FlowStyleManager::getInstance()
{
  if (m_instance.isNull()) m_instance.reset(new FlowStyleManager);

  return *m_instance;
}

void FlowStyleManager::deleteInstance() { m_instance.reset(nullptr); }

FlowStyleManager::FlowStyleManager()
{
  resetNodeStyles(Type::Normal);
  resetNodeStyles(Type::Selected);
  resetNodeStyles(Type::Hovered);
  resetNodeStyles(Type::Selected | Type::Hovered);
}

FlowStyleManager::~FlowStyleManager() = default;

void FlowStyleManager::setNodeStyles(Types types, NodeStyles &&styles)
{
  m_node_styles[types] = std::move(styles);
}

void FlowStyleManager::resetNodeStyles(Types types)
{
  auto style = NodeStyles{
    .font = QFont(),
    .margins = QMarginsF(4, 8, 4, 4),
    .gradient =
      {QColor(160, 160, 164), QColor(80, 80, 80), QColor(64, 64, 64),
       QColor(58, 58, 58)},
    .gradient_scale = {0.0, 0.3, 0.97, 1.0},
    .border_color = QColor(255, 255, 255),
    .border_radius = 3.0,
    .border_size = 1.0,

    .pin = NodeStyles::PinStyles{
      .font = QFont(),
      .size = QSizeF(2, 2),
      .margins = QMarginsF(8, 8, 8, 8),
      .color = QColor(169, 169, 169),
      .border_color = QColor(255, 255, 255)}};

  if (types.testFlag(Type::Selected)) style.border_color = QColor(255, 165, 0);
  if (types.testFlag(Type::Hovered)) style.border_size = 2.0;

  m_node_styles[types] = std::move(style);
}

const NodeStyles &FlowStyleManager::getNodeStyles(Types types)
{
  return m_node_styles.contains(types) ? m_node_styles[types]
                                       : m_node_styles[Type::Normal];
}

const NodeStyles &FlowStyleManager::getNodeStyles(const FlowNodeItem &node_item)
{
  auto style_type = FlowStyleManager::Types{FlowStyleManager::Type::Normal};
  if (node_item.isHovered()) style_type |= FlowStyleManager::Type::Hovered;
  if (node_item.isSelected()) style_type |= FlowStyleManager::Type::Selected;

  return getNodeStyles(style_type);
}