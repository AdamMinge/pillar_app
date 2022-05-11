#ifndef FLOW_FLOW_STYLE_MANAGER_H
#define FLOW_FLOW_STYLE_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QColor>
#include <QFont>
#include <QLinearGradient>
#include <QMargins>
#include <QObject>
#include <QSizeF>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

struct NodeStyles {
  struct PinStyles {
    QFont font;
    QSizeF size;
    QMarginsF margins;
    QColor color;
    QColor border_color;
  };

  QFont font;
  QMarginsF margins;
  QColor gradient[4];
  float gradient_scale[4];
  QColor border_color;
  float border_radius;
  float border_size;
  PinStyles pin;
};

class FlowNodeItem;

class FLOW_DOCUMENT_API FlowStyleManager : public QObject
{
  Q_OBJECT

public:
  enum class Type
  {
    Normal = 0,
    Selected = 1 << 0,
    Hovered = 1 << 1,
    SelectedAndHovered = Selected | Hovered
  };
  Q_DECLARE_FLAGS(Types, Type);

public:
  [[nodiscard]] static FlowStyleManager &getInstance();
  static void deleteInstance();

  void setNodeStyles(Types type, NodeStyles &&styles);
  void resetNodeStyles(Types type);

  [[nodiscard]] const NodeStyles &getNodeStyles(Types type);
  [[nodiscard]] const NodeStyles &getNodeStyles(const FlowNodeItem &node_item);

public:
  ~FlowStyleManager() override;

private:
  explicit FlowStyleManager();

private:
  static QScopedPointer<FlowStyleManager> m_instance;

  std::map<Types, NodeStyles> m_node_styles;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(FlowStyleManager::Types)

#endif//FLOW_FLOW_STYLE_MANAGER_H
