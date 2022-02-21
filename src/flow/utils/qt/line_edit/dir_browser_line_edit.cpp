/* ------------------------------------ Qt ---------------------------------- */
#include <QAction>
#include <QIcon>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qt/line_edit/dir_browser_line_edit.h"
/* ----------------------------------- utils -------------------------------- */
#include <flow/utils/qt/dialog/extended_file_dialog.h>
/* -------------------------------------------------------------------------- */

namespace utils
{

  QtDirBrowserLineEdit::QtDirBrowserLineEdit(QWidget *parent)
      : QLineEdit(parent)
  {
    auto browser_action = addAction(
      QIcon(":/shared/images/32x32/file_browser.png"),
      QLineEdit::TrailingPosition);

    connect(
      browser_action, &QAction::triggered, this,
      &QtDirBrowserLineEdit::browserPressed);
  }

  QtDirBrowserLineEdit::~QtDirBrowserLineEdit() = default;

  void QtDirBrowserLineEdit::setBrowserCaption(const QString &caption)
  {
    m_browser_caption = caption;
    Q_EMIT browserCaptionChanged(m_browser_caption);
  }

  void QtDirBrowserLineEdit::setBrowserDir(const QString &dir)
  {
    m_browser_dir = dir;
    Q_EMIT browserDirChanged(m_browser_dir);
  }

  QString QtDirBrowserLineEdit::getBrowserCaption() const
  {
    return m_browser_caption;
  }

  QString QtDirBrowserLineEdit::getBrowserDir() const { return m_browser_dir; }

  void QtDirBrowserLineEdit::browserPressed()
  {
    const auto file_name = QtExtendedFileDialog::getExistingDirectory(
      this, m_browser_caption, m_browser_dir);

    if (!file_name.isEmpty()) setText(file_name);
  }

}// namespace utils
