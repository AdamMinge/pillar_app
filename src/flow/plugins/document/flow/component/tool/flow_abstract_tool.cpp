/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/component/tool/flow_abstract_tool.h"
#include "flow/plugins/document/flow/component/scene/flow_scene.h"
#include "flow/plugins/document/flow/component/scene/flow_view.h"
/* -------------------------------------------------------------------------- */

FlowAbstractTool::FlowAbstractTool(
  QString name, QIcon icon, const QKeySequence &shortcut, QObject *parent)
    : QObject(parent), m_document(nullptr), m_name(std::move(name)),
      m_icon(std::move(icon)), m_cursor(Qt::ArrowCursor), m_shortcut(shortcut),
      m_enabled(true), m_visible(true), m_scene(nullptr)
{}

FlowAbstractTool::~FlowAbstractTool() = default;

void FlowAbstractTool::setDocument(FlowDocument *document)
{
  m_document = document;
}

FlowDocument *FlowAbstractTool::getDocument() const { return m_document; }

void FlowAbstractTool::setName(QString name) { m_name = std::move(name); }

void FlowAbstractTool::setIcon(QIcon icon) { m_icon = std::move(icon); }

void FlowAbstractTool::setShortcut(const QKeySequence &shortcut)
{
  m_shortcut = shortcut;
}

void FlowAbstractTool::setCursor(QCursor cursor)
{
  if (m_cursor.shape() == cursor.shape()) return;

  m_cursor = std::move(cursor);
  Q_EMIT cursorChanged(m_cursor);
}

void FlowAbstractTool::setEnabled(bool enabled)
{
  m_enabled = enabled;
  Q_EMIT enabledChanged(m_enabled);
}

void FlowAbstractTool::setVisible(bool visible)
{
  m_visible = visible;
  Q_EMIT visibleChanged(m_visible);
}

QString FlowAbstractTool::getName() const { return m_name; }

QIcon FlowAbstractTool::getIcon() const { return m_icon; }

QKeySequence FlowAbstractTool::getShortcut() const { return m_shortcut; }

QCursor FlowAbstractTool::getCursor() const { return m_cursor; }

bool FlowAbstractTool::isVisible() const { return m_visible; }

bool FlowAbstractTool::isEnabled() const { return m_enabled; }

void FlowAbstractTool::activate(FlowScene *scene) { m_scene = scene; }

void FlowAbstractTool::deactivate() { m_scene = nullptr; }

FlowScene *FlowAbstractTool::getScene() const { return m_scene; }

void FlowAbstractTool::keyPressEvent(QKeyEvent *event) {}

void FlowAbstractTool::keyReleaseEvent(QKeyEvent *event) {}

void FlowAbstractTool::mouseMoved(QGraphicsSceneMouseEvent *event) {}

void FlowAbstractTool::mousePressed(QGraphicsSceneMouseEvent *event) {}

void FlowAbstractTool::mouseReleased(QGraphicsSceneMouseEvent *event) {}
