#ifndef FLOW_FLOW_STYLE_H
#define FLOW_FLOW_STYLE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QColor>
#include <QFont>
#include <QMargins>
#include <QSizeF>
/* --------------------------------- Standard ------------------------------- */
#include <map>
#include <optional>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

/* --------------------------------- PinStyle ------------------------------- */

class PinStyle
{
public:
  enum class State
  {
    Normal = 0,
    Selected = 1 << 0,
    Hovered = 1 << 1
  };
  Q_DECLARE_FLAGS(States, State);

public:
  explicit PinStyle(const QList<const PinStyle *> &parents = {});
  ~PinStyle();

  void setFont(const std::optional<QFont> &font);
  void setFontColor(const std::optional<QColor> &color);
  void setSize(const std::optional<QSizeF> &size);
  void setMargins(const std::optional<QMarginsF> &margins);
  void setColor(const std::optional<QColor> &color);
  void setBorderColor(const std::optional<QColor> &color);

  [[nodiscard]] const std::optional<QFont> &getFont() const;
  [[nodiscard]] const std::optional<QColor> &getFontColor() const;
  [[nodiscard]] const std::optional<QSizeF> &getSize() const;
  [[nodiscard]] const std::optional<QMarginsF> &getMargins() const;
  [[nodiscard]] const std::optional<QColor> &getColor() const;
  [[nodiscard]] const std::optional<QColor> &getBorderColor() const;

  [[nodiscard]] const QFont &findFont() const;
  [[nodiscard]] const QColor &findFontColor() const;
  [[nodiscard]] const QSizeF &findSize() const;
  [[nodiscard]] const QMarginsF &findMargins() const;
  [[nodiscard]] const QColor &findColor() const;
  [[nodiscard]] const QColor &findBorderColor() const;

  void copy(const PinStyle &style);

private:
  struct Data {
    std::optional<QFont> font;
    std::optional<QColor> font_color;
    std::optional<QSizeF> size;
    std::optional<QMarginsF> margins;
    std::optional<QColor> color;
    std::optional<QColor> border_color;
  };

  template<typename TYPE>
  const TYPE &getProperty(std::optional<TYPE> Data::*property) const;

private:
  QList<const PinStyle *> m_parents;
  Data m_data;
};

template<typename TYPE>
const TYPE &PinStyle::getProperty(std::optional<TYPE> Data::*property) const
{
  if ((m_data.*property).has_value()) return (m_data.*property).value();
  for (auto parent : m_parents)
  {
    if ((parent->m_data.*property).has_value())
      return (parent->m_data.*property).value();
  }

  Q_ASSERT_X(
    false, "PinStyle::getProperty",
    "The property must be set for at least one instance");
}

Q_DECLARE_OPERATORS_FOR_FLAGS(PinStyle::States)

/* --------------------------------- NodeStyle ------------------------------ */

class NodeStyle
{
public:
  enum class State
  {
    Normal = 0,
    Selected = 1 << 0,
    Hovered = 1 << 1
  };
  Q_DECLARE_FLAGS(States, State);

public:
  explicit NodeStyle(const QList<const NodeStyle *> &parents = {});
  ~NodeStyle();

  void setFont(const std::optional<QFont> &font);
  void setFontColor(const std::optional<QColor> &color);
  void setMargins(const std::optional<QMarginsF> &margins);
  void setGradient(const std::optional<std::array<QColor, 4>> &gradient);
  void
  setGradientScale(const std::optional<std::array<float, 4>> &gradient_scale);
  void setBorderColor(const std::optional<QColor> &color);
  void setBorderRadius(std::optional<float> radius);
  void setBorderSize(std::optional<float> size);

  [[nodiscard]] const std::optional<QFont> &getFont() const;
  [[nodiscard]] const std::optional<QColor> &getFontColor() const;
  [[nodiscard]] const std::optional<QMarginsF> &getMargins() const;
  [[nodiscard]] const std::optional<std::array<QColor, 4>> &getGradient() const;
  [[nodiscard]] const std::optional<std::array<float, 4>> &
  getGradientScale() const;
  [[nodiscard]] const std::optional<QColor> &getBorderColor() const;
  [[nodiscard]] std::optional<float> getBorderRadius() const;
  [[nodiscard]] std::optional<float> getBorderSize() const;

  [[nodiscard]] const QFont &findFont() const;
  [[nodiscard]] const QColor &findFontColor() const;
  [[nodiscard]] const QMarginsF &findMargins() const;
  [[nodiscard]] const std::array<QColor, 4> &findGradient() const;
  [[nodiscard]] const std::array<float, 4> &findGradientScale() const;
  [[nodiscard]] const QColor &findBorderColor() const;
  [[nodiscard]] float findBorderRadius() const;
  [[nodiscard]] float findBorderSize() const;

  void copy(const NodeStyle &style);

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

  template<typename TYPE>
  const TYPE &getProperty(std::optional<TYPE> Data::*property) const;

private:
  QList<const NodeStyle *> m_parents;
  Data m_data;
};

template<typename TYPE>
const TYPE &NodeStyle::getProperty(std::optional<TYPE> Data::*property) const
{
  if ((m_data.*property).has_value()) return (m_data.*property).value();
  for (auto parent : m_parents)
  {
    if ((parent->m_data.*property).has_value())
      return (parent->m_data.*property).value();
  }

  Q_ASSERT_X(
    false, "NodeStyle::getProperty",
    "The property must be set for at least one instance");
}

Q_DECLARE_OPERATORS_FOR_FLAGS(NodeStyle::States)

/* --------------------------------- FlowStyle ------------------------------ */

class FlowStyle
{
public:
  explicit FlowStyle();
  ~FlowStyle();

  void setNodeStyle(const NodeStyle &style, NodeStyle::State state);
  [[nodiscard]] const NodeStyle &getNodeStyle(NodeStyle::States states) const;

  void setPinStyle(const PinStyle &style, PinStyle::State state);
  [[nodiscard]] const PinStyle &getPinStyle(PinStyle::States states) const;

private:
  [[nodiscard]] NodeStyle &getOrCreateNodeStyle(NodeStyle::States states);
  [[nodiscard]] PinStyle &getOrCreatePinStyle(PinStyle::States states);

private:
  std::map<NodeStyle::States, NodeStyle> m_node_styles;
  std::map<PinStyle::States, PinStyle> m_pin_styles;
};

#endif//FLOW_FLOW_STYLE_H
