/* ----------------------------------- Local--------------------------------- */
#include "flow/utils/qt/stacked_widget/stacked_widget_label.h"
#include "flow/utils/qt/stacked_widget/stacked_widget_tree_model.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "ui_stacked_widget_label.h"
/* -------------------------------------------------------------------------- */

namespace utils
{

  QtStackedWidgetLabel::QtStackedWidgetLabel(QWidget *parent)
      : QWidget(parent), m_ui(new Ui::QtStackedWidgetLabel), m_view(nullptr)
  {
    initUi();
    initConnections();

    retranslateUi();
  }

  QtStackedWidgetLabel::~QtStackedWidgetLabel() = default;

  void QtStackedWidgetLabel::setView(QAbstractItemView *view)
  {
    if (m_view == view) return;

    if (m_view && m_view->selectionModel())
    {
      disconnect(
        m_view->selectionModel(), &QItemSelectionModel::selectionChanged, this,
        &QtStackedWidgetLabel::selectionChanged);
    }

    m_view = view;

    if (m_view && m_view->selectionModel())
    {
      connect(
        m_view->selectionModel(), &QItemSelectionModel::selectionChanged, this,
        &QtStackedWidgetLabel::selectionChanged);
    }

    selectionChanged(QItemSelection{}, QItemSelection{});
  }

  const QAbstractItemView *QtStackedWidgetLabel::getView() const
  {
    return m_view;
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
  }

  void QtStackedWidgetLabel::initUi() { m_ui->setupUi(this); }

  void QtStackedWidgetLabel::initConnections() {}

  void QtStackedWidgetLabel::retranslateUi() { m_ui->retranslateUi(this); }

}// namespace utils