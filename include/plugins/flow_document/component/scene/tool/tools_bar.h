#ifndef FLOW_DOCUMENT_TOOLS_BAR_H
#define FLOW_DOCUMENT_TOOLS_BAR_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAction>
#include <QActionGroup>
#include <QToolBar>
/* ---------------------------------- Egnite -------------------------------- */
#include <egnite/plugin_listener.h>
/* ----------------------------------- Local -------------------------------- */
#include "flow_document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

class FlowDocument;

class Tool;
class ToolFactory;

class FLOW_DOCUMENT_API ToolsBar : public QToolBar,
                                   public egnite::PluginListener<ToolFactory> {
  Q_OBJECT

 public:
  explicit ToolsBar(QWidget *parent);
  ~ToolsBar() override;

  void setDocument(FlowDocument *document);
  [[nodiscard]] FlowDocument *getDocument() const;

  [[nodiscard]] QAction *registerTool(Tool *tool);
  void unregisterTool(Tool *tool);

  bool selectTool(Tool *tool);
  [[nodiscard]] Tool *getSelectedTool() const;

  QAction *findAction(Tool *tool);

 Q_SIGNALS:
  void toolSelected(Tool *tool);

 protected:
  void changeEvent(QEvent *event) override;

  void addedObject(ToolFactory *factory) override;
  void removedObject(ToolFactory *factory) override;

 private Q_SLOTS:
  void toolActivate(QAction *action);

  void toolEnabledChanged(bool enabled);
  void toolVisibleChanged(bool visible);

 private:
  void initUi();
  void initConnections();
  void retranslateUi();

 private:
  FlowDocument *m_document;
  QActionGroup *m_action_group;
  Tool *m_selected_tool;

  QHash<ToolFactory *, Tool *> m_tool_for_factory;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_TOOLS_BAR_H
