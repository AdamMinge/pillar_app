/* ----------------------------------- Local -------------------------------- */
#include "console_dock.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QEvent>
#include <QMenu>
#include <QShortcut>
#include <QVBoxLayout>
/* ---------------------------------- Pillar -------------------------------- */
#include <pillar/logging_manager.h>
#include <pillar/script_manager.h>
/* ----------------------------------- Qtils -------------------------------- */
#include <qtils/color/color.h>
#include <qtils/dpi/dpi.h>
#include <qtils/line_edit/line_edit_with_history.h>
/* -------------------------------------------------------------------------- */

/* ---------------------------- ConsoleOutputWidget ------------------------- */

void ConsoleOutputWidget::contextMenuEvent(QContextMenuEvent *event) {
  std::unique_ptr<QMenu> menu{createStandardContextMenu(event->pos())};

  menu->addSeparator();
  menu->addAction(tr("Clear Console"), this, &QPlainTextEdit::clear);

  menu->exec(event->globalPos());
}

/* -------------------------------- ConsoleDock ----------------------------- */

ConsoleDock::ConsoleDock(QWidget *parent)
    : QDockWidget(parent),
      m_plain_text_edit(new ConsoleOutputWidget()),
      m_line_edit_with_history(new qtils::QtLineEditWithHistory()),
      m_clear_button(new QPushButton(tr("Clear Console"))) {
  setObjectName(QLatin1String("Scene"));

  initUi();
  initConnections();

  retranslateUi();
}

ConsoleDock::~ConsoleDock() = default;

void ConsoleDock::changeEvent(QEvent *event) {
  QDockWidget::changeEvent(event);

  switch (event->type()) {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void ConsoleDock::onReport(const QString &str, const QColor &color) {
  m_plain_text_edit->appendHtml(
      QLatin1String("<pre style='color:%1'>").arg(qtils::getColorName(color)) +
      str.toHtmlEscaped() + QLatin1String("</pre>"));
}

void ConsoleDock::onInfoLog(const QString &message) { onReport(message); }

void ConsoleDock::onWarningLog(const QString &message) {
  onReport(message, QColor("orange"));
}

void ConsoleDock::onErrorLog(const QString &message) {
  onReport(message, QColor("red"));
}

void ConsoleDock::onScriptReport(const QString &str) {
  onReport(str, QColor("lightgreen"));
}

void ConsoleDock::onScriptResultReport(const QString &str) {
  onReport(str, QColor("gray"));
}

void ConsoleDock::executeScript() {
  const auto script = m_line_edit_with_history->text();
  if (script.isEmpty()) return;

  onScriptReport(script);
  const auto result = pillar::ScriptManager::getInstance().evaluate(script);
  if (!result.isError() && !result.isUndefined())
    onScriptResultReport(result.toString());

  m_line_edit_with_history->appendToHistory(script);
}

void ConsoleDock::initUi() {
  m_line_edit_with_history->setPlaceholderText("Execute script");

  m_plain_text_edit->setReadOnly(true);
  auto palette = m_plain_text_edit->palette();
  palette.setColor(QPalette::Base, Qt::black);
  palette.setColor(QPalette::Text, Qt::lightGray);
  m_plain_text_edit->setPalette(palette);

  auto widget = new QWidget(this);
  auto layout = new QVBoxLayout(widget);
  auto bottomBar = new QHBoxLayout();

  bottomBar->addWidget(m_line_edit_with_history);
  bottomBar->addWidget(m_clear_button);
  bottomBar->setSpacing(qtils::dpiScaled(2));

  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->addWidget(m_plain_text_edit);
  layout->addLayout(bottomBar);

  setWidget(widget);
}

void ConsoleDock::initConnections() {
  auto prev_shortcut = new QShortcut(Qt::Key_Up, m_line_edit_with_history,
                                     nullptr, nullptr, Qt::WidgetShortcut);
  auto next_shortcut = new QShortcut(Qt::Key_Down, m_line_edit_with_history,
                                     nullptr, nullptr, Qt::WidgetShortcut);

  connect(m_line_edit_with_history, &QLineEdit::returnPressed, this,
          &ConsoleDock::executeScript);
  connect(prev_shortcut, &QShortcut::activated, m_line_edit_with_history,
          &qtils::QtLineEditWithHistory::movePrev);
  connect(next_shortcut, &QShortcut::activated, m_line_edit_with_history,
          &qtils::QtLineEditWithHistory::moveNext);
  connect(m_clear_button, &QPushButton::clicked, m_plain_text_edit,
          &QPlainTextEdit::clear);

  auto &logging_manager = pillar::LoggingManager::getInstance();
  connect(&logging_manager, &pillar::LoggingManager::onInfoLog, this,
          &ConsoleDock::onInfoLog);
  connect(&logging_manager, &pillar::LoggingManager::onWarningLog, this,
          &ConsoleDock::onWarningLog);
  connect(&logging_manager, &pillar::LoggingManager::onErrorLog, this,
          &ConsoleDock::onErrorLog);
}

void ConsoleDock::retranslateUi() { setWindowTitle(tr("Console")); }
