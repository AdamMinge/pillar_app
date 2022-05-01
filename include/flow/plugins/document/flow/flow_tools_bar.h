#ifndef FLOW_FLOW_TOOLS_BAR_H
#define FLOW_FLOW_TOOLS_BAR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QToolBar>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FLOW_DOCUMENT_API FlowToolsBar : public QToolBar
{
  Q_OBJECT

public:
  explicit FlowToolsBar(QWidget *parent);
  ~FlowToolsBar() override;
};

#endif//FLOW_FLOW_TOOLS_BAR_H
