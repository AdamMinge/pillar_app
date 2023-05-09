/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/scene/tool/abstract_tool.h"

#include "flow_document/component/scene/flow_scene.h"
#include "flow_document/component/scene/flow_view.h"
/* -------------------------------------------------------------------------- */

namespace flow_document {

AbstractTool::AbstractTool(QString name, QIcon icon,
                           const QKeySequence &shortcut, QObject *parent)
    : QObject(parent),
      m_document(nullptr),
      m_name(std::move(name)),
      m_icon(std::move(icon)),
      m_cursor(Qt::ArrowCursor),
      m_shortcut(shortcut),
      m_enabled(true),
      m_visible(true),
      m_scene(nullptr) {}

AbstractTool::~AbstractTool() = default;

void AbstractTool::setDocument(FlowDocument *document) {
  m_document = document;
}

FlowDocument *AbstractTool::getDocument() const { return m_document; }

void AbstractTool::setName(QString name) { m_name = std::move(name); }

void AbstractTool::setIcon(QIcon icon) { m_icon = std::move(icon); }

void AbstractTool::setShortcut(const QKeySequence &shortcut) {
  m_shortcut = shortcut;
}

void AbstractTool::setCursor(QCursor cursor) {
  if (m_cursor.shape() == cursor.shape()) return;

  m_cursor = std::move(cursor);
  Q_EMIT cursorChanged(m_cursor);
}

void AbstractTool::setEnabled(bool enabled) {
  m_enabled = enabled;
  Q_EMIT enabledChanged(m_enabled);
}

void AbstractTool::setVisible(bool visible) {
  m_visible = visible;
  Q_EMIT visibleChanged(m_visible);
}

QString AbstractTool::getName() const { return m_name; }

QIcon AbstractTool::getIcon() const { return m_icon; }

QKeySequence AbstractTool::getShortcut() const { return m_shortcut; }

QCursor AbstractTool::getCursor() const { return m_cursor; }

bool AbstractTool::isVisible() const { return m_visible; }

bool AbstractTool::isEnabled() const { return m_enabled; }

void AbstractTool::activate(FlowScene *scene) { m_scene = scene; }

void AbstractTool::deactivate() { m_scene = nullptr; }

FlowScene *AbstractTool::getScene() const { return m_scene; }

void AbstractTool::keyPressEvent(QKeyEvent *event) {}

void AbstractTool::keyReleaseEvent(QKeyEvent *event) {}

void AbstractTool::mouseMoved(QGraphicsSceneMouseEvent *event) {}

void AbstractTool::mousePressed(QGraphicsSceneMouseEvent *event) {}

void AbstractTool::mouseReleased(QGraphicsSceneMouseEvent *event) {}

}  // namespace flow_document