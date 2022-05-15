/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/scene/flow_style.h"
/* -------------------------------------------------------------------------- */

/* --------------------------------- PinStyle ------------------------------- */

PinStyle::PinStyle(const QList<const PinStyle *> &parents) : m_parents(parents)
{}

PinStyle::~PinStyle() = default;

void PinStyle::setFont(const std::optional<QFont> &font) { m_data.font = font; }

void PinStyle::setFontColor(const std::optional<QColor> &color)
{
  m_data.font_color = color;
}

void PinStyle::setSize(const std::optional<QSizeF> &size)
{
  m_data.size = size;
}

void PinStyle::setMargins(const std::optional<QMarginsF> &margins)
{
  m_data.margins = margins;
}

void PinStyle::setColor(const std::optional<QColor> &color)
{
  m_data.color = color;
}

void PinStyle::setBorderColor(const std::optional<QColor> &color)
{
  m_data.border_color = color;
}

const std::optional<QFont> &PinStyle::getFont() const { return m_data.font; }

const std::optional<QColor> &PinStyle::getFontColor() const
{
  return m_data.font_color;
}

const std::optional<QSizeF> &PinStyle::getSize() const { return m_data.size; }

const std::optional<QMarginsF> &PinStyle::getMargins() const
{
  return m_data.margins;
}

const std::optional<QColor> &PinStyle::getColor() const { return m_data.color; }

const std::optional<QColor> &PinStyle::getBorderColor() const
{
  return m_data.border_color;
}

const QFont &PinStyle::findFont() const { return getProperty(&Data::font); }

const QColor &PinStyle::findFontColor() const
{
  return getProperty(&Data::font_color);
}

const QSizeF &PinStyle::findSize() const { return getProperty(&Data::size); }

const QMarginsF &PinStyle::findMargins() const
{
  return getProperty(&Data::margins);
}

const QColor &PinStyle::findColor() const { return getProperty(&Data::color); }

const QColor &PinStyle::findBorderColor() const
{
  return getProperty(&Data::border_color);
}

void PinStyle::copy(const PinStyle &style) { m_data = style.m_data; }

/* --------------------------------- NodeStyle ------------------------------ */

NodeStyle::NodeStyle(const QList<const NodeStyle *> &parents)
    : m_parents(parents)
{}

NodeStyle::~NodeStyle() = default;

void NodeStyle::setFont(const std::optional<QFont> &font)
{
  m_data.font = font;
}

void NodeStyle::setFontColor(const std::optional<QColor> &color)
{
  m_data.font_color = color;
}

void NodeStyle::setMargins(const std::optional<QMarginsF> &margins)
{
  m_data.margins = margins;
}

void NodeStyle::setGradient(
  const std::optional<std::array<QColor, 4>> &gradient)
{
  m_data.gradient = gradient;
}

void NodeStyle::setGradientScale(
  const std::optional<std::array<float, 4>> &gradient_scale)
{
  m_data.gradient_scale = gradient_scale;
}

void NodeStyle::setBorderColor(const std::optional<QColor> &color)
{
  m_data.border_color = color;
}

void NodeStyle::setBorderRadius(std::optional<float> radius)
{
  m_data.border_radius = radius;
}

void NodeStyle::setBorderSize(std::optional<float> size)
{
  m_data.border_size = size;
}

const std::optional<QFont> &NodeStyle::getFont() const { return m_data.font; }

const std::optional<QColor> &NodeStyle::getFontColor() const
{
  return m_data.font_color;
}

const std::optional<QMarginsF> &NodeStyle::getMargins() const
{
  return m_data.margins;
}

const std::optional<std::array<QColor, 4>> &NodeStyle::getGradient() const
{
  return m_data.gradient;
}

const std::optional<std::array<float, 4>> &NodeStyle::getGradientScale() const
{
  return m_data.gradient_scale;
}

const std::optional<QColor> &NodeStyle::getBorderColor() const
{
  return m_data.border_color;
}

std::optional<float> NodeStyle::getBorderRadius() const
{
  return m_data.border_radius;
}

std::optional<float> NodeStyle::getBorderSize() const
{
  return m_data.border_size;
}

const QFont &NodeStyle::findFont() const { return getProperty(&Data::font); }

const QColor &NodeStyle::findFontColor() const
{
  return getProperty(&Data::font_color);
}

const QMarginsF &NodeStyle::findMargins() const
{
  return getProperty(&Data::margins);
}

const std::array<QColor, 4> &NodeStyle::findGradient() const
{
  return getProperty(&Data::gradient);
}

const std::array<float, 4> &NodeStyle::findGradientScale() const
{
  return getProperty(&Data::gradient_scale);
}

const QColor &NodeStyle::findBorderColor() const
{
  return getProperty(&Data::border_color);
}

float NodeStyle::findBorderRadius() const
{
  return getProperty(&Data::border_radius);
}

float NodeStyle::findBorderSize() const
{
  return getProperty(&Data::border_size);
}

void NodeStyle::copy(const NodeStyle &style) { m_data = style.m_data; }

/* --------------------------------- FlowStyle ------------------------------ */

FlowStyle::FlowStyle()
{
  m_node_styles[NodeStyle::State::Normal] = NodeStyle{};
  m_node_styles[NodeStyle::State::Selected] =
    NodeStyle({&m_node_styles[NodeStyle::State::Normal]});
  m_node_styles[NodeStyle::State::Hovered] =
    NodeStyle({&m_node_styles[NodeStyle::State::Normal]});

  m_pin_styles[PinStyle::State::Normal] = PinStyle{};
  m_pin_styles[PinStyle::State::Selected] =
    PinStyle({&m_pin_styles[PinStyle::State::Normal]});
  m_pin_styles[PinStyle::State::Hovered] =
    PinStyle({&m_pin_styles[PinStyle::State::Normal]});
}

FlowStyle::~FlowStyle() = default;

void FlowStyle::setNodeStyle(const NodeStyle &style, NodeStyle::State state)
{
  getOrCreateNodeStyle(state).copy(style);
}

const NodeStyle &FlowStyle::getNodeStyle(NodeStyle::States states) const
{
  return const_cast<FlowStyle *>(this)->getOrCreateNodeStyle(states);
}

void FlowStyle::setPinStyle(const PinStyle &style, PinStyle::State state)
{
  getOrCreatePinStyle(state).copy(style);
}

const PinStyle &FlowStyle::getPinStyle(PinStyle::States states) const
{
  return const_cast<FlowStyle *>(this)->getOrCreatePinStyle(states);
}

NodeStyle &FlowStyle::getOrCreateNodeStyle(NodeStyle::States states)
{
  if (m_node_styles.contains(states)) return m_node_styles.at(states);

  auto parent_styles =
    QList<const NodeStyle *>{&m_node_styles.at(NodeStyle::State::Normal)};
  for (auto state : {NodeStyle::State::Selected, NodeStyle::State::Hovered})
  {
    if (!states.testFlag(state)) continue;
    auto &parent_style = m_node_styles.at(state);
    parent_styles.prepend(&parent_style);
  }

  m_node_styles[states] = NodeStyle(parent_styles);
  return m_node_styles.at(states);
}

PinStyle &FlowStyle::getOrCreatePinStyle(PinStyle::States states)
{
  if (m_pin_styles.contains(states)) return m_pin_styles.at(states);

  auto parent_styles =
    QList<const PinStyle *>{&m_pin_styles.at(PinStyle::State::Normal)};
  for (auto state : {PinStyle::State::Selected, PinStyle::State::Hovered})
  {
    if (!states.testFlag(state)) continue;
    auto &parent_style = m_pin_styles.at(state);
    parent_styles.prepend(&parent_style);
  }

  m_pin_styles[states] = PinStyle(parent_styles);
  return m_pin_styles.at(states);
}
