/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/flow_style.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* --------------------------------- PinStyle ------------------------------- */

PinStyle::PinStyle() = default;

PinStyle::~PinStyle() = default;

void PinStyle::setFont(const std::optional<QFont> &font, State state) {
  m_state_data[state].font = font;
}

void PinStyle::setFontColor(const std::optional<QColor> &color, State state) {
  m_state_data[state].font_color = color;
}

void PinStyle::setSize(const std::optional<QSizeF> &size, State state) {
  m_state_data[state].size = size;
}

void PinStyle::setMargins(const std::optional<QMarginsF> &margins,
                          State state) {
  m_state_data[state].margins = margins;
}

void PinStyle::setColor(const std::optional<QColor> &color, State state) {
  m_state_data[state].color = color;
}

void PinStyle::setBorderColor(const std::optional<QColor> &color, State state) {
  m_state_data[state].border_color = color;
}

const QFont &PinStyle::getFont(States states) const {
  return getProperty(&Data::font, states);
}

const QColor &PinStyle::getFontColor(States states) const {
  return getProperty(&Data::font_color, states);
}

const QSizeF &PinStyle::getSize(States states) const {
  return getProperty(&Data::size, states);
}

const QMarginsF &PinStyle::getMargins(States states) const {
  return getProperty(&Data::margins, states);
}

const QColor &PinStyle::getColor(States states) const {
  return getProperty(&Data::color, states);
}

const QColor &PinStyle::getBorderColor(States states) const {
  return getProperty(&Data::border_color, states);
}

bool PinStyle::isFontOverridden(State state) const {
  return m_state_data.at(state).font.has_value();
}

bool PinStyle::isFontColorOverridden(State state) const {
  return m_state_data.at(state).font_color.has_value();
}

bool PinStyle::isSizeOverridden(State state) const {
  return m_state_data.at(state).size.has_value();
}

bool PinStyle::isMarginsOverridden(State state) const {
  return m_state_data.at(state).margins.has_value();
}

bool PinStyle::isColorOverridden(State state) const {
  return m_state_data.at(state).color.has_value();
}

bool PinStyle::isBorderColorOverridden(State state) const {
  return m_state_data.at(state).border_color.has_value();
}

/* --------------------------------- NodeStyle ------------------------------ */

NodeStyle::NodeStyle() = default;

NodeStyle::~NodeStyle() = default;

void NodeStyle::setFont(const std::optional<QFont> &font, State state) {
  m_state_data[state].font = font;
}

void NodeStyle::setFontColor(const std::optional<QColor> &color, State state) {
  m_state_data[state].font_color = color;
}

void NodeStyle::setMargins(const std::optional<QMarginsF> &margins,
                           State state) {
  m_state_data[state].margins = margins;
}

void NodeStyle::setGradient(
    const std::optional<std::array<QColor, 4>> &gradient, State state) {
  m_state_data[state].gradient = gradient;
}

void NodeStyle::setGradientScale(
    const std::optional<std::array<float, 4>> &gradient_scale, State state) {
  m_state_data[state].gradient_scale = gradient_scale;
}

void NodeStyle::setBorderColor(const std::optional<QColor> &color,
                               State state) {
  m_state_data[state].border_color = color;
}

void NodeStyle::setBorderRadius(std::optional<float> radius, State state) {
  m_state_data[state].border_radius = radius;
}

void NodeStyle::setBorderSize(std::optional<float> size, State state) {
  m_state_data[state].border_size = size;
}

const QFont &NodeStyle::getFont(States states) const {
  return getProperty(&Data::font, states);
}

const QColor &NodeStyle::getFontColor(States states) const {
  return getProperty(&Data::font_color, states);
}

const QMarginsF &NodeStyle::getMargins(States states) const {
  return getProperty(&Data::margins, states);
}

const std::array<QColor, 4> &NodeStyle::getGradient(States states) const {
  return getProperty(&Data::gradient, states);
}

const std::array<float, 4> &NodeStyle::getGradientScale(States states) const {
  return getProperty(&Data::gradient_scale, states);
}

const QColor &NodeStyle::getBorderColor(States states) const {
  return getProperty(&Data::border_color, states);
}

float NodeStyle::getBorderRadius(States states) const {
  return getProperty(&Data::border_radius, states);
}

float NodeStyle::getBorderSize(States states) const {
  return getProperty(&Data::border_size, states);
}

bool NodeStyle::isFontOverridden(State state) const {
  return m_state_data.at(state).font.has_value();
}

bool NodeStyle::isFontColorOverridden(State state) const {
  return m_state_data.at(state).font_color.has_value();
}

bool NodeStyle::isMarginsOverridden(State state) const {
  return m_state_data.at(state).margins.has_value();
}

bool NodeStyle::isGradientOverridden(State state) const {
  return m_state_data.at(state).gradient.has_value();
}

bool NodeStyle::isGradientScaleOverridden(State state) const {
  return m_state_data.at(state).gradient_scale.has_value();
}

bool NodeStyle::isBorderColorOverridden(State state) const {
  return m_state_data.at(state).border_color.has_value();
}

bool NodeStyle::isBorderRadiusOverridden(State state) const {
  return m_state_data.at(state).border_radius.has_value();
}

bool NodeStyle::isBorderSizeOverridden(State state) const {
  return m_state_data.at(state).border_size.has_value();
}

/* --------------------------------- FlowStyle ------------------------------ */

FlowStyle::FlowStyle() = default;

FlowStyle::~FlowStyle() = default;

void FlowStyle::setNodeStyle(const NodeStyle &style) { m_node_style = style; }

const NodeStyle &FlowStyle::getNodeStyle() const { return m_node_style; }

const FlowStyle::NodeStyleViewer &FlowStyle::getNodeStyleViewer(
    NodeStyle::States states) const {
  if (!m_node_style_viewers.contains(states))
    m_node_style_viewers.insert(
        std::make_pair(states, NodeStyleViewer(m_node_style, states)));

  return m_node_style_viewers.at(states);
}

void FlowStyle::setPinStyle(const PinStyle &style) { m_pin_style = style; }

const PinStyle &FlowStyle::getPinStyle() const { return m_pin_style; }

const FlowStyle::PinStyleViewer &FlowStyle::getPinStyleViewer(
    PinStyle::States states) const {
  if (!m_pin_styles_viewers.contains(states))
    m_pin_styles_viewers.insert(
        std::make_pair(states, PinStyleViewer(m_pin_style, states)));

  return m_pin_styles_viewers.at(states);
}

/* ------------------------------- PinStateStyle ---------------------------- */

FlowStyle::PinStyleViewer::PinStyleViewer(const PinStyle &style,
                                          PinStyle::States states)
    : m_style(style), m_states(states) {}

FlowStyle::PinStyleViewer::~PinStyleViewer() = default;

const QFont &FlowStyle::PinStyleViewer::getFont() const {
  return m_style.getFont(m_states);
}

const QColor &FlowStyle::PinStyleViewer::getFontColor() const {
  return m_style.getFontColor(m_states);
}

const QSizeF &FlowStyle::PinStyleViewer::getSize() const {
  return m_style.getSize(m_states);
}

const QMarginsF &FlowStyle::PinStyleViewer::getMargins() const {
  return m_style.getMargins(m_states);
}

const QColor &FlowStyle::PinStyleViewer::getColor() const {
  return m_style.getColor(m_states);
}

const QColor &FlowStyle::PinStyleViewer::getBorderColor() const {
  return m_style.getBorderColor(m_states);
}

/* ------------------------------- NodeStateStyle --------------------------- */

FlowStyle::NodeStyleViewer::NodeStyleViewer(const NodeStyle &style,
                                            NodeStyle::States states)
    : m_style(style), m_states(states) {}

FlowStyle::NodeStyleViewer::~NodeStyleViewer() = default;

const QFont &FlowStyle::NodeStyleViewer::getFont() const {
  return m_style.getFont(m_states);
}

const QColor &FlowStyle::NodeStyleViewer::getFontColor() const {
  return m_style.getFontColor(m_states);
}

const QMarginsF &FlowStyle::NodeStyleViewer::getMargins() const {
  return m_style.getMargins(m_states);
}

const std::array<QColor, 4> &FlowStyle::NodeStyleViewer::getGradient() const {
  return m_style.getGradient(m_states);
}

const std::array<float, 4> &FlowStyle::NodeStyleViewer::getGradientScale()
    const {
  return m_style.getGradientScale(m_states);
}

const QColor &FlowStyle::NodeStyleViewer::getBorderColor() const {
  return m_style.getBorderColor(m_states);
}

float FlowStyle::NodeStyleViewer::getBorderRadius() const {
  return m_style.getBorderRadius(m_states);
}

float FlowStyle::NodeStyleViewer::getBorderSize() const {
  return m_style.getBorderSize(m_states);
}

}  // namespace flow_document