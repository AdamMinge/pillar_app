#ifndef FLOW_DOCUMENT_STYLE_H
#define FLOW_DOCUMENT_STYLE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QColor>
#include <QFont>
#include <QMargins>
#include <QSizeF>
#include <QVariantMap>
/* ----------------------------------- Local -------------------------------- */
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

using Gradient = std::array<QColor, 4>;
using GradientScale = std::array<float, 4>;

/* --------------------------------- PinStyle ------------------------------- */

class PinStyle {
 public:
  explicit PinStyle();
  ~PinStyle();

  void setFont(QFont font);
  void setFontColor(QColor color);
  void setSize(QSizeF size);
  void setMargins(QMarginsF margins);
  void setColor(QColor color);
  void setBorderColor(QColor color);

  [[nodiscard]] const QFont& getFont() const;
  [[nodiscard]] const QColor& getFontColor() const;
  [[nodiscard]] const QSizeF& getSize() const;
  [[nodiscard]] const QMarginsF& getMargins() const;
  [[nodiscard]] const QColor& getColor() const;
  [[nodiscard]] const QColor& getBorderColor() const;

 private:
  QFont m_font;
  QColor m_font_color;
  QSizeF m_size;
  QMarginsF m_margins;
  QColor m_color;
  QColor m_border_color;
};

/* --------------------------------- NodeStyle ------------------------------ */

class NodeStyle {
 public:
  explicit NodeStyle();
  ~NodeStyle();

  void setFont(QFont font);
  void setFontColor(QColor color);
  void setMargins(QMarginsF margins);
  void setGradient(Gradient gradient);
  void setGradientScale(GradientScale scale);
  void setBorderColor(QColor color);
  void setBorderRadius(float radius);
  void setBorderSize(float size);

  [[nodiscard]] const QFont& getFont() const;
  [[nodiscard]] const QColor& getFontColor() const;
  [[nodiscard]] const QMarginsF& getMargins() const;
  [[nodiscard]] const Gradient& getGradient() const;
  [[nodiscard]] const GradientScale& getGradientScale() const;
  [[nodiscard]] const QColor& getBorderColor() const;
  [[nodiscard]] float getBorderRadius() const;
  [[nodiscard]] float getBorderSize() const;

 private:
  QFont m_font;
  QColor m_font_color;
  QMarginsF m_margins;
  Gradient m_gradient;
  GradientScale m_gradient_scale;
  QColor m_border_color;
  float m_border_radius;
  float m_border_size;
};

/* ------------------------------ ConnectionStyle --------------------------- */

class ConnectionStyle {
 public:
  explicit ConnectionStyle();
  ~ConnectionStyle();

  void setColor(QColor color);
  void setThickness(float thickness);

  [[nodiscard]] const QColor& getColor() const;
  [[nodiscard]] float getThickness() const;

 private:
  QColor m_color;
  float m_thickness;
};

/* --------------------------------- FlowStyle ------------------------------ */

class FlowStyle {
 public:
  explicit FlowStyle();
  ~FlowStyle();

  void setNodeStyle(const NodeStyle& style);
  [[nodiscard]] const NodeStyle& getNodeStyle() const;

  void setPinStyle(const PinStyle& style);
  [[nodiscard]] const PinStyle& getPinStyle() const;

  void setConnectionStyle(const ConnectionStyle& style);
  [[nodiscard]] const ConnectionStyle& getConnectionStyle() const;

 private:
  NodeStyle m_node_style;
  PinStyle m_pin_style;
  ConnectionStyle m_connection_style;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_STYLE_H
