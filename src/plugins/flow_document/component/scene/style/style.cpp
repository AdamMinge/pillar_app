/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/style/style.h"
/* -------------------------------------------------------------------------- */

namespace {

constexpr QLatin1String PROP_FONT("FONT");
constexpr QLatin1String PROP_FONT_COLOR("FONT_COLOR");
constexpr QLatin1String PROP_SIZE("SIZE");
constexpr QLatin1String PROP_MARGINS("MARGINS");
constexpr QLatin1String PROP_COLOR("COLOR");
constexpr QLatin1String PROP_BORDER_COLOR("BORDER_COLOR");
constexpr QLatin1String PROP_BORDER_RADIUS("PROP_BORDER_RADIUS");
constexpr QLatin1String PROP_BORDER_SIZE("PROP_BORDER_SIZE");
constexpr QLatin1String PROP_GRADIENT("PROP_GRADIENT");
constexpr QLatin1String PROP_GRADIENT_SCALE("PROP_GRADIENT_SCALE");

}  // namespace

namespace flow_document {

/* -------------------------------- ObjectStyle ---------------------------- */

ObjectStyle::ObjectStyle() = default;

ObjectStyle::~ObjectStyle() = default;

/* --------------------------------- PinStyle ------------------------------ */

PinStyle::PinStyle() = default;

PinStyle::~PinStyle() = default;

void PinStyle::setFont(std::optional<QFont> font, State state) {
  setProperty(PROP_FONT, state, font);
}

void PinStyle::setFontColor(std::optional<QColor> color, State state) {
  setProperty(PROP_FONT_COLOR, state, color);
}

void PinStyle::setSize(std::optional<QSizeF> size, State state) {
  setProperty(PROP_SIZE, state, size);
}

void PinStyle::setMargins(std::optional<QMarginsF> margins, State state) {
  setProperty(PROP_MARGINS, state, margins);
}

void PinStyle::setColor(std::optional<QColor> color, State state) {
  setProperty(PROP_COLOR, state, color);
}

void PinStyle::setBorderColor(std::optional<QColor> color, State state) {
  setProperty(PROP_BORDER_COLOR, state, color);
}

QFont PinStyle::getFont(States states) const {
  return getProperty<QFont>(PROP_FONT, states);
}

QColor PinStyle::getFontColor(States states) const {
  return getProperty<QColor>(PROP_FONT_COLOR, states);
}

QSizeF PinStyle::getSize(States states) const {
  return getProperty<QSizeF>(PROP_SIZE, states);
}

QMarginsF PinStyle::getMargins(States states) const {
  return getProperty<QMarginsF>(PROP_MARGINS, states);
}

QColor PinStyle::getColor(States states) const {
  return getProperty<QColor>(PROP_COLOR, states);
}

QColor PinStyle::getBorderColor(States states) const {
  return getProperty<QColor>(PROP_BORDER_COLOR, states);
}

/* ------------------------------- PinStyleViewer -------------------------- */

PinStyleViewer::PinStyleViewer(const PinStyle &style,
                               ObjectStyle::States states)
    : m_style(style), m_states(states) {}

PinStyleViewer::~PinStyleViewer() = default;

QFont PinStyleViewer::getFont() const { return m_style.getFont(m_states); }

QColor PinStyleViewer::getFontColor() const {
  return m_style.getFontColor(m_states);
}

QSizeF PinStyleViewer::getSize() const { return m_style.getSize(m_states); }

QMarginsF PinStyleViewer::getMargins() const {
  return m_style.getMargins(m_states);
}

QColor PinStyleViewer::getColor() const { return m_style.getColor(m_states); }

QColor PinStyleViewer::getBorderColor() const {
  return m_style.getBorderColor(m_states);
}

/* --------------------------------- NodeStyle ----------------------------- */

NodeStyle::NodeStyle() = default;

NodeStyle::~NodeStyle() = default;

void NodeStyle::setFont(std::optional<QFont> font, State state) {
  setProperty(PROP_FONT, state, font);
}

void NodeStyle::setFontColor(std::optional<QColor> color, State state) {
  setProperty(PROP_FONT_COLOR, state, color);
}

void NodeStyle::setMargins(std::optional<QMarginsF> margins, State state) {
  setProperty(PROP_MARGINS, state, margins);
}

void NodeStyle::setGradient(std::optional<Gradient> gradient, State state) {
  setProperty(PROP_GRADIENT, state, gradient);
}

void NodeStyle::setGradientScale(std::optional<GradientScale> scale,
                                 State state) {
  setProperty(PROP_GRADIENT_SCALE, state, scale);
}

void NodeStyle::setBorderColor(std::optional<QColor> color, State state) {
  setProperty(PROP_BORDER_COLOR, state, color);
}

void NodeStyle::setBorderRadius(std::optional<float> radius, State state) {
  setProperty(PROP_BORDER_RADIUS, state, radius);
}

void NodeStyle::setBorderSize(std::optional<float> size, State state) {
  setProperty(PROP_BORDER_SIZE, state, size);
}

QFont NodeStyle::getFont(States states) const {
  return getProperty<QFont>(PROP_FONT, states);
}

QColor NodeStyle::getFontColor(States states) const {
  return getProperty<QColor>(PROP_FONT_COLOR, states);
}

QMarginsF NodeStyle::getMargins(States states) const {
  return getProperty<QMarginsF>(PROP_MARGINS, states);
}

Gradient NodeStyle::getGradient(States states) const {
  return getProperty<Gradient>(PROP_GRADIENT, states);
}

GradientScale NodeStyle::getGradientScale(States states) const {
  return getProperty<GradientScale>(PROP_GRADIENT_SCALE, states);
}

QColor NodeStyle::getBorderColor(States states) const {
  return getProperty<QColor>(PROP_BORDER_COLOR, states);
}

float NodeStyle::getBorderRadius(States states) const {
  return getProperty<float>(PROP_BORDER_RADIUS, states);
}

float NodeStyle::getBorderSize(States states) const {
  return getProperty<float>(PROP_BORDER_SIZE, states);
}

/* ------------------------------ NodeStyleViewer --------------------------- */

NodeStyleViewer::NodeStyleViewer(const NodeStyle &style,
                                 ObjectStyle::States states)
    : m_style(style), m_states(states) {}

NodeStyleViewer::~NodeStyleViewer() = default;

QFont NodeStyleViewer::getFont() const { return m_style.getFont(m_states); }

QColor NodeStyleViewer::getFontColor() const {
  return m_style.getFontColor(m_states);
}

QMarginsF NodeStyleViewer::getMargins() const {
  return m_style.getMargins(m_states);
}

Gradient NodeStyleViewer::getGradient() const {
  return m_style.getGradient(m_states);
}

GradientScale NodeStyleViewer::getGradientScale() const {
  return m_style.getGradientScale(m_states);
}

QColor NodeStyleViewer::getBorderColor() const {
  return m_style.getBorderColor(m_states);
}

float NodeStyleViewer::getBorderRadius() const {
  return m_style.getBorderRadius(m_states);
}

float NodeStyleViewer::getBorderSize() const {
  return m_style.getBorderSize(m_states);
}

/* --------------------------------- FlowStyle ------------------------------ */

FlowStyle::FlowStyle() = default;

FlowStyle::~FlowStyle() = default;

void FlowStyle::setNodeStyle(const NodeStyle &style) { m_node_style = style; }

const NodeStyle &FlowStyle::getNodeStyle() const { return m_node_style; }

NodeStyleViewer FlowStyle::getNodeStyleViewer(
    ObjectStyle::States states) const {
  return NodeStyleViewer(m_node_style, states);
}

void FlowStyle::setPinStyle(const PinStyle &style) { m_pin_style = style; }

const PinStyle &FlowStyle::getPinStyle() const { return m_pin_style; }

PinStyleViewer FlowStyle::getPinStyleViewer(ObjectStyle::States states) const {
  return PinStyleViewer(m_pin_style, states);
}

}  // namespace flow_document