/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/scene/flow_style_manager.h"
#include "flow/plugins/document/flow/component/scene/flow_style_reader.h"
#include "flow/plugins/document/flow/component/scene/flow_style_writer.h"
/* -------------------------------------------------------------------------- */

QScopedPointer<FlowStyleManager> FlowStyleManager::m_instance =
  QScopedPointer<FlowStyleManager>(nullptr);

FlowStyleManager &FlowStyleManager::getInstance()
{
  if (m_instance.isNull()) m_instance.reset(new FlowStyleManager);

  return *m_instance;
}

void FlowStyleManager::deleteInstance() { m_instance.reset(nullptr); }

FlowStyleManager::FlowStyleManager() { resetStyle(); }

FlowStyleManager::~FlowStyleManager() = default;

void FlowStyleManager::setStyle(const FlowStyle &style) { *m_style = style; }

void FlowStyleManager::resetStyle()
{
  loadStyle(":/plugins/document/flow/styles/flow/default.json");
}

bool FlowStyleManager::loadStyle(const QString &file_name)
{
  auto reader = FlowStyleReader{};
  auto loaded_style = reader.read(file_name);
  if (!loaded_style) return false;

  m_style = std::move(loaded_style);
  return true;
}

bool FlowStyleManager::saveStyle(const QString &file_name)
{
  auto reader = FlowStyleWriter{};
  return reader.write(*m_style, file_name);
}

const FlowStyle &FlowStyleManager::getStyle() const { return *m_style; }

const FlowStyle::NodeStyleViewer &getNodeStyle(const FlowNodeItem &item)
{
  auto state = NodeStyle::States{NodeStyle::State::Normal};
  if (item.isSelected()) state |= NodeStyle::State::Selected;
  if (item.isHovered()) state |= NodeStyle::State::Hovered;

  const auto &node_style =
    FlowStyleManager::getInstance().getStyle().getNodeStyleViewer(state);
  return node_style;
}

const FlowStyle::PinStyleViewer &getPinStyle(const FlowNodeItem &item)
{
  auto state = PinStyle::States{PinStyle::State::Normal};
  if (item.isSelected()) state |= PinStyle::State::Selected;
  if (item.isHovered()) state |= PinStyle::State::Hovered;

  const auto &pin_style =
    FlowStyleManager::getInstance().getStyle().getPinStyleViewer(state);
  return pin_style;
}
