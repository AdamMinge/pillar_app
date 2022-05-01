#ifndef FLOW_FLOW_TOOLS_MANAGER_H
#define FLOW_FLOW_TOOLS_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAction>
#include <QActionGroup>
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FlowDocument;
class FlowAbstractTool;

class FLOW_DOCUMENT_API FlowToolsManager : public QObject
{
  Q_OBJECT

public:
  [[nodiscard]] static FlowToolsManager &getInstance();
  static void deleteInstance();

public:
  ~FlowToolsManager() override;

  void setDocument(FlowDocument *document);
  [[nodiscard]] FlowDocument *getDocument() const;

  [[nodiscard]] QAction *registerTool(FlowAbstractTool *tool);
  void unregisterTool(FlowAbstractTool *tool);

  bool selectTool(FlowAbstractTool *tool);
  [[nodiscard]] FlowAbstractTool *getSelectedTool() const;

Q_SIGNALS:
  void toolSelected(FlowAbstractTool *tool);

protected:
  explicit FlowToolsManager();

  QAction *findAction(FlowAbstractTool *tool);

private Q_SLOTS:
  void toolActivate(QAction *action);

  void toolEnabledChanged(bool enabled);
  void toolVisibleChanged(bool visible);

private:
  static QScopedPointer<FlowToolsManager> m_instance;

  FlowDocument *m_document;
  QActionGroup *m_action_group;
  FlowAbstractTool *m_selected_tool;
};

#endif//FLOW_FLOW_TOOLS_MANAGER_H
