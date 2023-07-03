#ifndef FLOW_DOCUMENT_STYLE_H
#define FLOW_DOCUMENT_STYLE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QColor>
#include <QFont>
#include <QMargins>
#include <QSizeF>
#include <QVariantMap>
/* --------------------------------- Standard ------------------------------- */
#include <map>
#include <optional>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

using Gradient = std::array<QColor, 4>;
using GradientScale = std::array<float, 4>;

/* -------------------------------- ObjectStyle ----------------------------- */

class ObjectStyle {
 public:
  enum class State { Normal = 0, Selected = 1 << 0, Hovered = 1 << 1 };
  Q_DECLARE_FLAGS(States, State);

 public:
  explicit ObjectStyle();
  ~ObjectStyle();

 protected:
  template <typename TYPE>
  TYPE getProperty(const QString &key, States states) const;

  template <typename TYPE>
  void setProperty(const QString &key, State state,
                   std::optional<TYPE> opt_value);

 private:
  QMap<State, QVariantMap> m_state_data;
};

template <typename TYPE>
TYPE ObjectStyle::getProperty(const QString &key, States states) const {
  for (auto state : {State::Hovered, State::Selected}) {
    if (!states.testFlag(state)) continue;

    if (m_state_data[state].contains(key))
      return m_state_data[state][key].template value<TYPE>();
  }

  Q_ASSERT_X(m_state_data[State::Normal].contains(key),
             "ObjectStyle::getProperty",
             "The property must be set for at least for normal state");
  return m_state_data[State::Normal][key].value<TYPE>();
}

template <typename TYPE>
void ObjectStyle::setProperty(const QString &key, State state,
                              std::optional<TYPE> opt_value) {
  if (opt_value.has_value())
    m_state_data[state][key] = QVariant::fromValue<TYPE>(opt_value.value());
  else
    m_state_data[state].remove(key);
}

Q_DECLARE_OPERATORS_FOR_FLAGS(ObjectStyle::States)

/* --------------------------------- PinStyle ------------------------------- */

class PinStyle : public ObjectStyle {
 public:
  explicit PinStyle();
  ~PinStyle();

  void setFont(std::optional<QFont> font, State state);
  void setFontColor(std::optional<QColor> color, State state);
  void setSize(std::optional<QSizeF> size, State state);
  void setMargins(std::optional<QMarginsF> margins, State state);
  void setColor(std::optional<QColor> color, State state);
  void setBorderColor(std::optional<QColor> color, State state);

  [[nodiscard]] QFont getFont(States states) const;
  [[nodiscard]] QColor getFontColor(States states) const;
  [[nodiscard]] QSizeF getSize(States states) const;
  [[nodiscard]] QMarginsF getMargins(States states) const;
  [[nodiscard]] QColor getColor(States states) const;
  [[nodiscard]] QColor getBorderColor(States states) const;
};

/* ----------------------------- PinStyleViewer --------------------------- */

class PinStyleViewer {
 public:
  explicit PinStyleViewer(const PinStyle &style, ObjectStyle::States states);
  ~PinStyleViewer();

  [[nodiscard]] QFont getFont() const;
  [[nodiscard]] QColor getFontColor() const;
  [[nodiscard]] QSizeF getSize() const;
  [[nodiscard]] QMarginsF getMargins() const;
  [[nodiscard]] QColor getColor() const;
  [[nodiscard]] QColor getBorderColor() const;

 private:
  const PinStyle &m_style;
  ObjectStyle::States m_states;
};

/* --------------------------------- NodeStyle ------------------------------ */

class NodeStyle : public ObjectStyle {
 public:
  explicit NodeStyle();
  ~NodeStyle();

  void setFont(std::optional<QFont> font, State state);
  void setFontColor(std::optional<QColor> color, State state);
  void setMargins(std::optional<QMarginsF> margins, State state);
  void setGradient(std::optional<Gradient> gradient, State state);
  void setGradientScale(std::optional<GradientScale> scale, State state);
  void setBorderColor(std::optional<QColor> color, State state);
  void setBorderRadius(std::optional<float> radius, State state);
  void setBorderSize(std::optional<float> size, State state);

  [[nodiscard]] QFont getFont(States states) const;
  [[nodiscard]] QColor getFontColor(States states) const;
  [[nodiscard]] QMarginsF getMargins(States states) const;
  [[nodiscard]] Gradient getGradient(States states) const;
  [[nodiscard]] GradientScale getGradientScale(States states) const;
  [[nodiscard]] QColor getBorderColor(States states) const;
  [[nodiscard]] float getBorderRadius(States states) const;
  [[nodiscard]] float getBorderSize(States states) const;
};

/* ----------------------------- NodeStyleViewer -------------------------- */

class NodeStyleViewer {
 public:
  explicit NodeStyleViewer(const NodeStyle &style, ObjectStyle::States states);
  ~NodeStyleViewer();

  [[nodiscard]] QFont getFont() const;
  [[nodiscard]] QColor getFontColor() const;
  [[nodiscard]] QMarginsF getMargins() const;
  [[nodiscard]] Gradient getGradient() const;
  [[nodiscard]] GradientScale getGradientScale() const;
  [[nodiscard]] QColor getBorderColor() const;
  [[nodiscard]] float getBorderRadius() const;
  [[nodiscard]] float getBorderSize() const;

 private:
  const NodeStyle &m_style;
  ObjectStyle::States m_states;
};

/* --------------------------------- FlowStyle ------------------------------ */

class FlowStyle {
 public:
  explicit FlowStyle();
  ~FlowStyle();

  void setNodeStyle(const NodeStyle &style);
  [[nodiscard]] const NodeStyle &getNodeStyle() const;
  [[nodiscard]] NodeStyleViewer getNodeStyleViewer(
      ObjectStyle::States states) const;

  void setPinStyle(const PinStyle &style);
  [[nodiscard]] const PinStyle &getPinStyle() const;
  [[nodiscard]] PinStyleViewer getPinStyleViewer(
      ObjectStyle::States states) const;

 private:
  NodeStyle m_node_style;
  PinStyle m_pin_style;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_STYLE_H
