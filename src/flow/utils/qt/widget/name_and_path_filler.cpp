/* ------------------------------------ Qt ---------------------------------- */
#include <QDir>
#include <QEvent>
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qt/widget/name_and_path_filler.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "ui_name_and_path_filler.h"
/* -------------------------------------------------------------------------- */

namespace utils
{

  QtNameAndPathFiller::QtNameAndPathFiller(QWidget *parent)
      : QWidget(parent), m_ui(new Ui::QtNameAndPathFiller)
  {
    initUi();
    initConnections();

    retranslateUi();
  }

  QtNameAndPathFiller::~QtNameAndPathFiller() = default;

  QString QtNameAndPathFiller::getName() const
  {
    return m_ui->m_name_edit->text();
  }

  QString QtNameAndPathFiller::getPath() const
  {
    return m_ui->m_path_edit->text();
  }

  bool QtNameAndPathFiller::isValid() const
  {
    const auto hasNameError = !m_ui->m_name_error_message->text().isEmpty();
    const auto hasPathError = !m_ui->m_path_error_message->text().isEmpty();

    return !hasNameError && !hasPathError;
  }

  void QtNameAndPathFiller::changeEvent(QEvent *event)
  {
    QWidget::changeEvent(event);
    switch (event->type())
    {
      case QEvent::LanguageChange:
        retranslateUi();
        break;
      default:
        break;
    }
  }

  void QtNameAndPathFiller::nameChanged()
  {
    const auto name = m_ui->m_name_edit->text();

    auto error_message = QString{};
    if (name.isEmpty()) error_message = tr("Please enter some name");

    m_ui->m_name_error_message->setText(error_message);
    m_ui->m_name_error_message->setVisible(!error_message.isEmpty());

    Q_EMIT nameChanged(name);
    Q_EMIT validStateChanged(isValid());
  }

  void QtNameAndPathFiller::pathChanged()
  {
    const auto path = m_ui->m_path_edit->text();

    auto file_info = QFileInfo{path};
    auto dir = QDir{path};

    auto path_is_incorrect = !file_info.exists() || ((!file_info.isDir()) ||
                                                     (!file_info.isWritable()));
    auto dir_is_empty = !dir.isEmpty();

    auto error_message = QString{};
    if (path_is_incorrect || dir_is_empty)
      error_message = tr("Please choose an empty folder");

    m_ui->m_path_error_message->setText(error_message);
    m_ui->m_path_error_message->setVisible(!error_message.isEmpty());

    Q_EMIT pathChanged(path);
    Q_EMIT validStateChanged(isValid());
  }

  void QtNameAndPathFiller::initUi()
  {
    m_ui->setupUi(this);

    m_ui->m_path_edit->setBrowserCaption(tr("Select Directory"));
    m_ui->m_path_edit->setBrowserDir(QString{});

    nameChanged();
    pathChanged();
  }

  void QtNameAndPathFiller::initConnections()
  {
    connect(m_ui->m_name_edit, &QLineEdit::textChanged, this,
            qOverload<>(&QtNameAndPathFiller::nameChanged));
    connect(m_ui->m_path_edit, &QLineEdit::textChanged, this,
            qOverload<>(&QtNameAndPathFiller::pathChanged));
  }

  void QtNameAndPathFiller::retranslateUi() { m_ui->retranslateUi(this); }

}// namespace utils
