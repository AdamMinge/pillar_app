#ifndef FLOW_FLOW_ABSTRACT_TOOL_H
#define FLOW_FLOW_ABSTRACT_TOOL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAction>
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QIcon>
#include <QKeySequence>
#include <QObject>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FlowDocument;
class FlowScene;
class FlowView;

class FLOW_DOCUMENT_API FlowAbstractTool : public QObject
{
  Q_OBJECT

public:
  explicit FlowAbstractTool(
    QString name, QIcon icon, QCursor cursor, const QKeySequence &shortcut,
    QObject *parent = nullptr);
  ~FlowAbstractTool() override;

  void setDocument(FlowDocument *document);
  [[nodiscard]] FlowDocument *getDocument() const;

  void setName(QString name);
  void setIcon(QIcon icon);
  void setShortcut(const QKeySequence &shortcut);
  void setCursor(QCursor cursor);
  void setEnabled(bool enabled = true);
  void setVisible(bool visible = true);

  [[nodiscard]] QString getName() const;
  [[nodiscard]] QIcon getIcon() const;
  [[nodiscard]] QKeySequence getShortcut() const;
  [[nodiscard]] QCursor getCursor() const;
  [[nodiscard]] bool isVisible() const;
  [[nodiscard]] bool isEnabled() const;

  virtual void activate(FlowScene *scene);
  virtual void deactivate(FlowScene *scene);

  virtual void mouseMoved(QGraphicsSceneMouseEvent *event);
  virtual void mousePressed(QGraphicsSceneMouseEvent *event);
  virtual void mouseReleased(QGraphicsSceneMouseEvent *event);

Q_SIGNALS:
  void enabledChanged(bool enabled);
  void visibleChanged(bool visible);

protected:
  [[nodiscard]] static QGraphicsView *findView(QGraphicsSceneEvent *event);
  [[nodiscard]] static QGraphicsScene *findScene(QGraphicsSceneEvent *event);

private:
  FlowDocument *m_document;
  QString m_name;
  QIcon m_icon;
  QCursor m_cursor;
  QKeySequence m_shortcut;

  bool m_enabled;
  bool m_visible;
};

#endif//FLOW_FLOW_ABSTRACT_TOOL_H
