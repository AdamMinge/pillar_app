#ifndef FLOW_DOCUMENT_TOOL_H
#define FLOW_DOCUMENT_TOOL_H

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
#include "flow/document/export.h"
/* -------------------------------------------------------------------------- */

namespace flow {

class FlowDocument;
class FlowScene;
class FlowView;

class LIB_FLOW_DOCUMENT_API Tool : public QObject {
  Q_OBJECT

 public:
  explicit Tool(QString name, QIcon icon, const QKeySequence &shortcut,
                QObject *parent = nullptr);
  ~Tool() override;

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
  virtual void deactivate();

  [[nodiscard]] FlowScene *getScene() const;

  virtual void keyPressEvent(QKeyEvent *event);
  virtual void keyReleaseEvent(QKeyEvent *event);

  virtual void mouseMoved(QGraphicsSceneMouseEvent *event);
  virtual void mousePressed(QGraphicsSceneMouseEvent *event);
  virtual void mouseReleased(QGraphicsSceneMouseEvent *event);

 Q_SIGNALS:
  void enabledChanged(bool enabled);
  void visibleChanged(bool visible);
  void cursorChanged(const QCursor &cursor);

 private:
  FlowDocument *m_document;
  QString m_name;
  QIcon m_icon;
  QCursor m_cursor;
  QKeySequence m_shortcut;

  bool m_enabled;
  bool m_visible;

  FlowScene *m_scene;
};

}  // namespace flow

#endif  // FLOW_DOCUMENT_TOOL_H
