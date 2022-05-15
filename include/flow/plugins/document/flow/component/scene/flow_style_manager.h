#ifndef FLOW_FLOW_STYLE_MANAGER_H
#define FLOW_FLOW_STYLE_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* ---------------------------------- Standard ------------------------------ */
#include <memory>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/scene/flow_node_item.h"
#include "flow/plugins/document/flow/component/scene/flow_style.h"
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FlowStyle;

class FLOW_DOCUMENT_API FlowStyleManager : public QObject
{
  Q_OBJECT

public:
  [[nodiscard]] static FlowStyleManager &getInstance();
  static void deleteInstance();

public:
  ~FlowStyleManager() override;

  void setStyle(const FlowStyle &style);
  void resetStyle();

  bool loadStyle(const QString &file_name);
  bool saveStyle(const QString &file_name);

  [[nodiscard]] const FlowStyle &getStyle() const;

private:
  explicit FlowStyleManager();

private:
  static QScopedPointer<FlowStyleManager> m_instance;

  std::unique_ptr<FlowStyle> m_style;
};

const NodeStyle &getNodeStyle(const FlowNodeItem &item);
const PinStyle &getPinStyle(const FlowNodeItem &item);

#endif//FLOW_FLOW_STYLE_MANAGER_H
