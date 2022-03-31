/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QCheckBox>
#include <QFileInfo>
#include <QPainter>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings/plugin_list_delegate.h"
#include "flow/editor/settings/plugin_list_model.h"
/* -------------------------------------------------------------------------- */

PluginListDelegate::PluginListDelegate(QObject *parent)
    : QStyledItemDelegate(parent), m_icon_size(64, 64), m_margins(0, 0, 0, 0),
      m_spacing(0, 0)
{}

PluginListDelegate::~PluginListDelegate() = default;

QWidget *PluginListDelegate::createEditor(
  QWidget *parent, const QStyleOptionViewItem &option,
  const QModelIndex &index) const
{
  auto editor = new QCheckBox(parent);

  connect(
    editor, &QCheckBox::stateChanged, this, [this, editor, index](auto value) {
      setModelData(
        editor, const_cast<QAbstractItemModel *>(index.model()), index);
    });

  return editor;
}

void PluginListDelegate::setEditorData(
  QWidget *editor, const QModelIndex &index) const
{
  auto check_box = qobject_cast<QCheckBox *>(editor);
  const auto plugin_state =
    index.data(PluginListModel::Role::PluginStateRole).toBool();
  check_box->setChecked(plugin_state);
}

void PluginListDelegate::setModelData(
  QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  auto check_box = qobject_cast<QCheckBox *>(editor);
  int value = (check_box->checkState() == Qt::Checked) ? 1 : 0;
  model->setData(index, value, PluginListModel::Role::PluginStateRole);
}

void PluginListDelegate::updateEditorGeometry(
  QWidget *editor, const QStyleOptionViewItem &option,
  const QModelIndex &index) const
{
  QStyleOptionViewItem opt(option);
  initStyleOption(&opt, index);

  const auto &rect = opt.rect;
  const auto content_rect = rect.adjusted(
    m_margins.left(), m_margins.top(), -m_margins.right(), -m_margins.bottom());

  QStyleOptionButton checkbox_style;
  const auto checkbox_rect = QApplication::style()->subElementRect(
    QStyle::SE_CheckBoxIndicator, &checkbox_style);
  checkbox_style.rect = content_rect;
  checkbox_style.rect.setLeft(
    content_rect.x() + content_rect.width() - checkbox_rect.width());

  editor->setGeometry(checkbox_style.rect);
}

void PluginListDelegate::paint(
  QPainter *painter, const QStyleOptionViewItem &option,
  const QModelIndex &index) const
{
  QStyleOptionViewItem opt(option);
  initStyleOption(&opt, index);

  auto &palette = opt.palette;
  auto &rect = opt.rect;
  auto font = QFont(opt.font);
  auto content_rect = rect.adjusted(
    m_margins.left(), m_margins.top(), -m_margins.right(), -m_margins.bottom());

  const auto is_last_index = index.model()->rowCount() - 1 == index.row();
  const auto plugin_icon =
    index.data(PluginListModel::Role::PluginIcon).value<QIcon>();
  const auto plugin_name =
    index.data(PluginListModel::Role::PluginName).toString();
  const auto plugin_state =
    index.data(PluginListModel::Role::PluginStateRole).toBool();

  painter->save();

  painter->setClipping(true);
  painter->setClipRect(rect);
  painter->setFont(opt.font);

  painter->fillRect(
    rect, opt.state & QStyle::State_Selected ? palette.highlight().color()
                                             : palette.light().color());

  painter->drawLine(
    is_last_index ? rect.left() : content_rect.left(), rect.bottom(),
    rect.right(), rect.bottom());

  painter->drawPixmap(
    content_rect.left(), content_rect.top(), plugin_icon.pixmap(m_icon_size));

  auto plugin_name_rect =
    QFontMetrics(font).boundingRect(plugin_name).adjusted(0, 0, 1, 1);

  auto text_rect = content_rect.adjusted(
    m_icon_size.width() + m_spacing.width(),
    ((content_rect.height() / 2) - (plugin_name_rect.height() / 2)), 0, 0);

  font.setPointSizeF(opt.font.pointSize() * 1.4);
  painter->setFont(font);
  painter->setPen(palette.text().color());
  painter->drawText(text_rect, Qt::TextSingleLine, plugin_name);

  QStyleOptionButton checkbox_style;
  const auto checkbox_rect = QApplication::style()->subElementRect(
    QStyle::SE_CheckBoxIndicator, &checkbox_style);
  checkbox_style.rect = content_rect;
  checkbox_style.rect.setLeft(
    content_rect.x() + content_rect.width() - checkbox_rect.width());
  checkbox_style.state = plugin_state
                           ? (QStyle::State_On | QStyle::State_Enabled)
                           : (QStyle::State_Off | QStyle::State_Enabled);

  QApplication::style()->drawControl(
    QStyle::CE_CheckBox, &checkbox_style, painter);

  painter->restore();
}

QSize PluginListDelegate::sizeHint(
  const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QStyleOptionViewItem opt(option);
  initStyleOption(&opt, index);

  return QSize{
    opt.rect.width(),
    m_icon_size.height() + m_margins.top() + m_margins.bottom()};
}

void PluginListDelegate::setIconSize(const QSize &size) { m_icon_size = size; }

const QSize &PluginListDelegate::getIconSize() const { return m_icon_size; }

void PluginListDelegate::setMargins(const QMargins &margins)
{
  m_margins = margins;
}

const QMargins &PluginListDelegate::getMargins() const { return m_margins; }

void PluginListDelegate::setSpacing(
  int vertical_spacing, int horizontal_spacing)
{
  m_spacing.setWidth(vertical_spacing);
  m_spacing.setHeight(horizontal_spacing);
}

void PluginListDelegate::setVerticalSpacing(int spacing)
{
  m_spacing.setWidth(spacing);
}

void PluginListDelegate::setHorizontalSpacing(int spacing)
{
  m_spacing.setHeight(spacing);
}

int PluginListDelegate::getVerticalSpacing() const { return m_spacing.width(); }

int PluginListDelegate::getHorizontalSpacing() const
{
  return m_spacing.height();
}
