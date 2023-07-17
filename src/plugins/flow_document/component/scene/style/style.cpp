/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/style/style.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

/* --------------------------------- PinStyle ------------------------------ */

PinStyle::PinStyle() = default;

PinStyle::~PinStyle() = default;

void PinStyle::setFont(QFont font) { m_font = std::move(font); }

void PinStyle::setFontColor(QColor color) { m_font_color = std::move(color); }

void PinStyle::setSize(QSizeF size) { m_size = std::move(size); }

void PinStyle::setMargins(QMarginsF margins) { m_margins = std::move(margins); }

void PinStyle::setColor(QColor color) { m_color = std::move(color); }

void PinStyle::setBorderColor(QColor color) {
  m_border_color = std::move(color);
}

const QFont& PinStyle::getFont() const { return m_font; }

const QColor& PinStyle::getFontColor() const { return m_font_color; }

const QSizeF& PinStyle::getSize() const { return m_size; }

const QMarginsF& PinStyle::getMargins() const { return m_margins; }

const QColor& PinStyle::getColor() const { return m_color; }

const QColor& PinStyle::getBorderColor() const { return m_border_color; }

/* --------------------------------- NodeStyle ----------------------------- */

NodeStyle::NodeStyle() = default;

NodeStyle::~NodeStyle() = default;

void NodeStyle::setFont(QFont font) { m_font = std::move(font); }

void NodeStyle::setFontColor(QColor color) { m_font_color = std::move(color); }

void NodeStyle::setMargins(QMarginsF margins) {
  m_margins = std::move(margins);
}

void NodeStyle::setGradient(Gradient gradient) {
  m_gradient = std::move(gradient);
}

void NodeStyle::setGradientScale(GradientScale scale) {
  m_gradient_scale = std::move(scale);
}

void NodeStyle::setBorderColor(QColor color) {
  m_border_color = std::move(color);
}

void NodeStyle::setBorderRadius(float radius) { m_border_radius = radius; }

void NodeStyle::setBorderSize(float size) { m_border_size = size; }

const QFont& NodeStyle::getFont() const { return m_font; }

const QColor& NodeStyle::getFontColor() const { return m_font_color; }

const QMarginsF& NodeStyle::getMargins() const { return m_margins; }

const Gradient& NodeStyle::getGradient() const { return m_gradient; }

const GradientScale& NodeStyle::getGradientScale() const {
  return m_gradient_scale;
}

const QColor& NodeStyle::getBorderColor() const { return m_border_color; }

float NodeStyle::getBorderRadius() const { return m_border_radius; }

float NodeStyle::getBorderSize() const { return m_border_size; }

/* --------------------------------- FlowStyle ------------------------------ */

FlowStyle::FlowStyle() = default;

FlowStyle::~FlowStyle() = default;

void FlowStyle::setNodeStyle(const NodeStyle& style) { m_node_style = style; }

const NodeStyle& FlowStyle::getNodeStyle() const { return m_node_style; }

void FlowStyle::setPinStyle(const PinStyle& style) { m_pin_style = style; }

const PinStyle& FlowStyle::getPinStyle() const { return m_pin_style; }

}  // namespace flow_document