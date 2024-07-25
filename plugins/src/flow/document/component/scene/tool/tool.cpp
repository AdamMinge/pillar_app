/* ----------------------------------- Local -------------------------------- */
#include "flow/document/component/scene/tool/tool.h"

#include "flow/document/component/scene/scene.h"
#include "flow/document/component/scene/view.h"
/* -------------------------------------------------------------------------- */

namespace flow {

Tool::Tool(QString name, QIcon icon, const QKeySequence &shortcut,
           QObject *parent)
    : QObject(parent),
      m_document(nullptr),
      m_name(std::move(name)),
      m_icon(std::move(icon)),
      m_cursor(Qt::ArrowCursor),
      m_shortcut(shortcut),
      m_enabled(true),
      m_visible(true),
      m_scene(nullptr) {}

Tool::~Tool() = default;

void Tool::setDocument(FlowDocument *document) { m_document = document; }

FlowDocument *Tool::getDocument() const { return m_document; }

void Tool::setName(QString name) { m_name = std::move(name); }

void Tool::setIcon(QIcon icon) { m_icon = std::move(icon); }

void Tool::setShortcut(const QKeySequence &shortcut) { m_shortcut = shortcut; }

void Tool::setCursor(QCursor cursor) {
  if (m_cursor.shape() == cursor.shape()) return;

  m_cursor = std::move(cursor);
  Q_EMIT cursorChanged(m_cursor);
}

void Tool::setEnabled(bool enabled) {
  m_enabled = enabled;
  Q_EMIT enabledChanged(m_enabled);
}

void Tool::setVisible(bool visible) {
  m_visible = visible;
  Q_EMIT visibleChanged(m_visible);
}

QString Tool::getName() const { return m_name; }

QIcon Tool::getIcon() const { return m_icon; }

QKeySequence Tool::getShortcut() const { return m_shortcut; }

QCursor Tool::getCursor() const { return m_cursor; }

bool Tool::isVisible() const { return m_visible; }

bool Tool::isEnabled() const { return m_enabled; }

void Tool::activate(FlowScene *scene) { m_scene = scene; }

void Tool::deactivate() { m_scene = nullptr; }

FlowScene *Tool::getScene() const { return m_scene; }

void Tool::keyPressEvent(QKeyEvent *event) {}

void Tool::keyReleaseEvent(QKeyEvent *event) {}

void Tool::mouseMoved(QGraphicsSceneMouseEvent *event) {}

void Tool::mousePressed(QGraphicsSceneMouseEvent *event) {}

void Tool::mouseReleased(QGraphicsSceneMouseEvent *event) {}

}  // namespace flow