#ifndef FLOW_DOCUMENT_FLOW_TOOLS_BAR_H
#define FLOW_DOCUMENT_FLOW_TOOLS_BAR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAction>
#include <QActionGroup>
#include <QToolBar>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;
class FlowAbstractTool;

class FLOW_DOCUMENT_API FlowToolsBar : public QToolBar {
  Q_OBJECT

 public:
  explicit FlowToolsBar(QWidget *parent);
  ~FlowToolsBar() override;

  void setDocument(FlowDocument *document);
  [[nodiscard]] FlowDocument *getDocument() const;

  [[nodiscard]] QAction *registerTool(FlowAbstractTool *tool);
  void unregisterTool(FlowAbstractTool *tool);

  bool selectTool(FlowAbstractTool *tool);
  [[nodiscard]] FlowAbstractTool *getSelectedTool() const;

  QAction *findAction(FlowAbstractTool *tool);

 Q_SIGNALS:
  void toolSelected(FlowAbstractTool *tool);

 private Q_SLOTS:
  void toolActivate(QAction *action);

  void toolEnabledChanged(bool enabled);
  void toolVisibleChanged(bool visible);

 private:
  void initUi();
  void initConnections();

  void selectFirstTool();

 private:
  FlowDocument *m_document;
  QActionGroup *m_action_group;
  FlowAbstractTool *m_selected_tool;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_FLOW_TOOLS_BAR_H
