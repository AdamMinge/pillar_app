/* ----------------------------------- Local--------------------------------- */
#include "flow/utils/qt/stacked_widget/stacked_widget_label.h"
#include "flow/utils/qt/stacked_widget/stacked_widget_tree_model.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "ui_stacked_widget_label.h"
/* -------------------------------------------------------------------------- */

namespace utils
{

  QtStackedWidgetLabel::QtStackedWidgetLabel(QWidget *parent)
      : QWidget(parent), m_ui(new Ui::QtStackedWidgetLabel), m_view(nullptr),
        m_history({}), m_history_position(0), m_history_size(20)
  {
    initUi();
    initConnections();

    retranslateUi();
  }

  QtStackedWidgetLabel::~QtStackedWidgetLabel() = default;

  void QtStackedWidgetLabel::setView(QAbstractItemView *view)
  {
    if (m_view == view) return;

    if (auto selection_model = m_view ? m_view->selectionModel() : nullptr;
        selection_model)
    {
      disconnect(
        selection_model, &QItemSelectionModel::selectionChanged, this,
        &QtStackedWidgetLabel::selectionChanged);
      disconnect(
        selection_model, &QItemSelectionModel::modelChanged, this,
        &QtStackedWidgetLabel::modelChanged);
    }

    m_view = view;

    if (auto selection_model = m_view ? m_view->selectionModel() : nullptr;
        selection_model)
    {
      connect(
        selection_model, &QItemSelectionModel::selectionChanged, this,
        &QtStackedWidgetLabel::selectionChanged);
      connect(
        selection_model, &QItemSelectionModel::modelChanged, this,
        &QtStackedWidgetLabel::modelChanged);
    }

    modelChanged(m_view ? m_view->model() : nullptr);
    selectionChanged(QItemSelection{}, QItemSelection{});
  }

  const QAbstractItemView *QtStackedWidgetLabel::getView() const
  {
    return m_view;
  }

  void QtStackedWidgetLabel::setHistorySize(qsizetype size)
  {
    m_history_size = size;
    modelChanged(m_view ? m_view->model() : nullptr);
  }

  qsizetype QtStackedWidgetLabel::getHistorySize() const
  {
    return m_history_size;
  }

  void QtStackedWidgetLabel::changeEvent(QEvent *event)
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

  void QtStackedWidgetLabel::selectionChanged(
    const QItemSelection &selected, const QItemSelection &deselected)
  {
    const auto indexes = selected.indexes();
    if (!indexes.empty())
    {
      auto label_text = QString{};
      auto current_index = indexes.front();

      appendToHistory(current_index);
      while (current_index.isValid())
      {
        const auto name =
          current_index.data(QtStackedWidgetTreeModel::Role::NameRole)
            .toString();

        label_text = label_text.isEmpty()
                       ? name
                       : QString("%1 > %2").arg(name, label_text);

        current_index = current_index.parent();
      }

      m_ui->m_label->setText(label_text);
    } else if (!deselected.empty())
    {
      m_ui->m_label->clear();
    }

    updateActions();
  }

  void QtStackedWidgetLabel::modelChanged(QAbstractItemModel *model)
  {
    m_history.clear();
    m_history_position = 0;
  }

  void QtStackedWidgetLabel::moveHistory(qsizetype direction)
  {
    auto new_history_position =
      qBound(0, m_history_position + direction, m_history.size() - 1);

    m_history_position = new_history_position;

    Q_EMIT currentChanged(m_history[new_history_position]);
  }

  void QtStackedWidgetLabel::appendToHistory(const QModelIndex &index)
  {
    auto widget =
      index.data(QtStackedWidgetTreeModel::Role::WidgetRole).value<QWidget *>();

    if (
      m_history.empty() || (m_history_position < m_history.size() &&
                            m_history[m_history_position] != widget))
    {
      m_history =
        m_history.mid(
          m_history.size() == m_history_size ? 1 : 0, m_history_position + 1)
        << widget;
      m_history_position = m_history.size() - 1;
    }
  }

  void QtStackedWidgetLabel::initUi() { m_ui->setupUi(this); }

  void QtStackedWidgetLabel::initConnections()
  {
    connect(m_ui->m_prev_button, &QToolButton::pressed, this, [this]() {
      moveHistory(-1);
    });
    connect(m_ui->m_next_button, &QToolButton::pressed, this, [this]() {
      moveHistory(1);
    });
  }

  void QtStackedWidgetLabel::updateActions()
  {
    m_ui->m_prev_button->setEnabled(m_history_position != 0);
    m_ui->m_next_button->setEnabled(m_history_position < m_history.size() - 1);
  }

  void QtStackedWidgetLabel::retranslateUi() { m_ui->retranslateUi(this); }

}// namespace utils