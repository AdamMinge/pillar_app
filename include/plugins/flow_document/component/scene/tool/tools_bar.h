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

class AbstractTool;
class AbstractToolFactory;

class FLOW_DOCUMENT_API ToolsBar
    : public QToolBar,
      public egnite::PluginListener<AbstractToolFactory> {
  Q_OBJECT

 public:
  explicit ToolsBar(QWidget *parent);
  ~ToolsBar() override;

  void setDocument(FlowDocument *document);
  [[nodiscard]] FlowDocument *getDocument() const;

  [[nodiscard]] QAction *registerTool(AbstractTool *tool);
  void unregisterTool(AbstractTool *tool);

  bool selectTool(AbstractTool *tool);
  [[nodiscard]] AbstractTool *getSelectedTool() const;

  QAction *findAction(AbstractTool *tool);

 Q_SIGNALS:
  void toolSelected(AbstractTool *tool);

 protected:
  void changeEvent(QEvent *event) override;

  void addedObject(AbstractToolFactory *factory) override;
  void removedObject(AbstractToolFactory *factory) override;

 private Q_SLOTS:
  void toolActivate(QAction *action);

  void toolEnabledChanged(bool enabled);
  void toolVisibleChanged(bool visible);

 private:
  void initUi();
  void initConnections();
  void retranslateUi();

  void selectFirstTool();

 private:
  FlowDocument *m_document;
  QActionGroup *m_action_group;
  AbstractTool *m_selected_tool;

  QHash<AbstractToolFactory *, AbstractTool *> m_tool_for_factory;
};

}  // namespace flow_document

#endif  // FLOW_DOCUMENT_TOOLS_BAR_H
