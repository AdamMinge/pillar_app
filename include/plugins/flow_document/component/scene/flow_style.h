#ifndef FLOW_DOCUMENT_FLOW_STYLE_H
#define FLOW_DOCUMENT_FLOW_STYLE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QColor>
#include <QFont>
#include <QMargins>
#include <QSizeF>
/* --------------------------------- Standard ------------------------------- */
#include <map>
#include <optional>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

/* --------------------------------- PinStyle ------------------------------- */

namespace flow_document {

class PinStyle {
 public:
  enum class State { Normal = 0, Selected = 1 << 0, Hovered = 1 << 1 };
  Q_DECLARE_FLAGS(States, State);

 public:
  explicit PinStyle();
  ~PinStyle();

  void setFont(std::optional<QFont> font, State state);
  void setFontColor(std::optional<QColor> color, State state);
  void setSize(std::optional<QSizeF> size, State state);
  void setMargins(std::optional<QMarginsF> margins, State state);
  void setColor(std::optional<QColor> color, State state);
  void setBorderColor(std::optional<QColor> color, State state);

  [[nodiscard]] const QFont &getFont(States states) const;
  [[nodiscard]] const QColor &getFontColor(States states) const;
  [[nodiscard]] const QSizeF &getSize(States states) const;
  [[nodiscard]] const QMarginsF &getMargins(States states) const;
  [[nodiscard]] const QColor &getColor(States states) const;
  [[nodiscard]] const QColor &getBorderColor(States states) const;

  [[nodiscard]] bool isFontOverridden(State state) const;
  [[nodiscard]] bool isFontColorOverridden(State state) const;
  [[nodiscard]] bool isSizeOverridden(State state) const;
  [[nodiscard]] bool isMarginsOverridden(State state) const;
  [[nodiscard]] bool isColorOverridden(State state) const;
  [[nodiscard]] bool isBorderColorOverridden(State state) const;

 private:
  struct Data {
    std::optional<QFont> font;
    std::optional<QColor> font_color;
    std::optional<QSizeF> size;
    std::optional<QMarginsF> margins;
    std::optional<QColor> color;
    std::optional<QColor> border_color;
  };

  template <typename TYPE>
  const TYPE &getProperty(std::optional<TYPE> Data::*property,
                          States states) const;

 private:
  std::map<State, Data> m_state_data;
};

template <typename TYPE>
const TYPE &PinStyle::getProperty(std::optional<TYPE> Data::*property,
                                  States states) const {
  for (auto state : {State::Hovered, State::Selected}) {
    if (!states.testFlag(state)) continue;

    if ((m_state_data.at(state).*property).has_value())
      return (m_state_data.at(state).*property).value();
  }

  Q_ASSERT_X((m_state_data.at(State::Normal).*property).has_value(),
             "PinStyle::getProperty",
             "The property must be set for at least for normal state");
  return (m_state_data.at(State::Normal).*property).value();
}

Q_DECLARE_OPERATORS_FOR_FLAGS(PinStyle::States)

/* --------------------------------- NodeStyle ------------------------------ */

class NodeStyle {
 public:
  enum class State { Normal = 0, Selected = 1 << 0, Hovered = 1 << 1 };
  Q_DECLARE_FLAGS(States, State);

 public:
  explicit NodeStyle();
  ~NodeStyle();

  void setFont(std::optional<QFont> font, State state);
  void setFontColor(std::optional<QColor> color, State state);
  void setMargins(std::optional<QMarginsF> margins, State state);
  void setGradient(std::optional<std::array<QColor, 4>> gradient, State state);
  void setGradientScale(std::optional<std::array<float, 4>> gradient_scale,
                        State state);
  void setBorderColor(std::optional<QColor> color, State state);
  void setBorderRadius(std::optional<float> radius, State state);
  void setBorderSize(std::optional<float> size, State state);

  [[nodiscard]] const QFont &getFont(States states) const;
  [[nodiscard]] const QColor &getFontColor(States states) const;
  [[nodiscard]] const QMarginsF &getMargins(States states) const;
  [[nodiscard]] const std::array<QColor, 4> &getGradient(States states) const;
  [[nodiscard]] const std::array<float, 4> &getGradientScale(
      States states) const;
  [[nodiscard]] const QColor &getBorderColor(States states) const;
  [[nodiscard]] float getBorderRadius(States states) const;
  [[nodiscard]] float getBorderSize(States states) const;

  [[nodiscard]] bool isFontOverridden(State state) const;
  [[nodiscard]] bool isFontColorOverridden(State state) const;
  [[nodiscard]] bool isMarginsOverridden(State state) const;
  [[nodiscard]] bool isGradientOverridden(State state) const;
  [[nodiscard]] bool isGradientScaleOverridden(State state) const;
  [[nodiscard]] bool isBorderColorOverridden(State state) const;
  [[nodiscard]] bool isBorderRadiusOverridden(State state) const;
  [[nodiscard]] bool isBorderSizeOverridden(State state) const;

 private:
  struct Data {
    std::optional<QFont> font;
    std::optional<QColor> font_color;
    std::optional<QMarginsF> margins;
    std::optional<std::array<QColor, 4>> gradient;
    std::optional<std::array<float, 4>> gradient_scale;
    std::optional<QColor> border_color;
    std::optional<float> border_radius;
    std::optional<float> border_size;
  };

  template <typename TYPE>
  const TYPE &getProperty(std::optional<TYPE> Data::*property,
                          States states) const;

 private:
  std::map<State, Data> m_state_data;
};

template <typename TYPE>
const TYPE &NodeStyle::getProperty(std::optional<TYPE> Data::*property,
                                   States states) const {
  for (auto state : {State::Hovered, State::Selected}) {
    if (!states.testFlag(state)) continue;

    if ((m_state_data.at(state).*property).has_value())
      return (m_state_data.at(state).*property).value();
  }

  Q_ASSERT_X((m_state_data.at(State::Normal).*property).has_value(),
             "NodeStyle::getProperty",
             "The property must be set for at least for normal state");
  return (m_state_data.at(State::Normal).*property).value();
}

Q_DECLARE_OPERATORS_FOR_FLAGS(NodeStyle::States)

/* --------------------------------- FlowStyle ------------------------------ */

class FlowStyle {
 public:
  class NodeStyleViewer;
  class PinStyleViewer;

 public:
  explicit FlowStyle();
  ~FlowStyle();

  void setNodeStyle(const NodeStyle &style);
  [[nodiscard]] const NodeStyle &getNodeStyle() const;
  [[nodiscard]] const NodeStyleViewer &getNodeStyleViewer(
      NodeStyle::States states) const;

  void setPinStyle(const PinStyle &style);
  [[nodiscard]] const PinStyle &getPinStyle() const;
  [[nodiscard]] const PinStyleViewer &getPinStyleViewer(
      PinStyle::States states) const;

 private:
  mutable std::map<NodeStyle::States, NodeStyleViewer> m_node_styles_viewers;
  mutable std::map<PinStyle::States, PinStyleViewer> m_pin_styles_viewers;

  NodeStyle m_node_style;
  PinStyle m_pin_style;
};

/* ------------------------------- PinStyleViewer --------------------------- */

class FlowStyle::PinStyleViewer {
 public:
  explicit PinStyleViewer(const PinStyle &style, PinStyle::States states);
  ~PinStyleViewer();

  [[nodiscard]] const QFont &getFont() const;
  [[nodiscard]] const QColor &getFontColor() const;
  [[nodiscard]] const QSizeF &getSize() const;
  [[nodiscard]] const QMarginsF &getMargins() const;
  [[nodiscard]] const QColor &getColor() const;
  [[nodiscard]] const QColor &getBorderColor() const;

 private:
  const PinStyle &m_style;
  PinStyle::States m_states;
};

/* ------------------------------- NodeStyleViewer -------------------------- */

class FlowStyle::NodeStyleViewer {
 public:
  explicit NodeStyleViewer(const NodeStyle &style, NodeStyle::States states);
  ~NodeStyleViewer();

  [[nodiscard]] const QFont &getFont() const;
  [[nodiscard]] const QColor &getFontColor() const;
  [[nodiscard]] const QMarginsF &getMargins() const;
  [[nodiscard]] const std::array<QColor, 4> &getGradient() const;
  [[nodiscard]] const std::array<float, 4> &getGradientScale() const;
  [[nodiscard]] const QColor &getBorderColor() const;
  [[nodiscard]] float getBorderRadius() const;
  [[nodiscard]] float getBorderSize() const;

 private:
  const NodeStyle &m_style;
  NodeStyle::States m_states;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_STYLE_H
