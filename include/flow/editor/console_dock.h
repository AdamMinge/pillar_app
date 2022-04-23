#ifndef CONSOLE_DOCK_H
#define CONSOLE_DOCK_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDockWidget>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
/* -------------------------------------------------------------------------- */

namespace utils
{
  class QtLineEditWithHistory;
}

class ConsoleOutputWidget : public QPlainTextEdit
{
  Q_OBJECT

public:
  using QPlainTextEdit::QPlainTextEdit;

protected:
  void contextMenuEvent(QContextMenuEvent *event) override;
};

class ConsoleDock final : public QDockWidget
{
  Q_OBJECT

public:
  explicit ConsoleDock(QWidget *parent = nullptr);
  ~ConsoleDock() override;

protected:
  void changeEvent(QEvent *event) override;

private Q_SLOTS:
  void onReport(const QString &str, const QColor &color = QColor{});

  void onInfoLog(const QString &message);
  void onWarningLog(const QString &message);
  void onErrorLog(const QString &message);

  void onScriptReport(const QString &str);
  void onScriptResultReport(const QString &str);

  void executeScript();

private:
  void initUi();
  void initConnections();

  void retranslateUi();

private:
  QPlainTextEdit *m_plain_text_edit;
  utils::QtLineEditWithHistory *m_line_edit_with_history;
  QPushButton *m_clear_button;
};

#endif//CONSOLE_DOCK_H
