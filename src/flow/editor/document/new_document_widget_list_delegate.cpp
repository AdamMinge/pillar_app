/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
#include <QPainter>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/document/new_document_widget_list_delegate.h"
#include "flow/editor/document/new_document_widget_list_model.h"
/* -------------------------------------------------------------------------- */

NewDocumentWidgetListDelegate::NewDocumentWidgetListDelegate(QObject *parent)
    : QStyledItemDelegate(parent), m_icon_size(64, 64), m_margins(0, 0, 0, 0),
      m_spacing(0, 0)
{}

NewDocumentWidgetListDelegate::~NewDocumentWidgetListDelegate() = default;

void NewDocumentWidgetListDelegate::paint(
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

  auto is_last_index = index.model()->rowCount() - 1 == index.row();
  auto name = index.data(NewDocumentWidgetListModel::Role::NameRole).toString();

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
    content_rect.left(), content_rect.top(),
    index.data(NewDocumentWidgetListModel::Role::IconRole)
      .value<QIcon>()
      .pixmap(m_icon_size));

  auto text_rect = content_rect.adjusted(
    m_icon_size.width() + m_spacing.width(),
    static_cast<int>(
      (content_rect.top() + m_icon_size.height() - opt.font.pointSize() * 1.4) /
      2),
    0, 0);

  font.setPointSizeF(opt.font.pointSize() * 1.4);
  painter->setFont(font);
  painter->setPen(palette.text().color());
  painter->drawText(text_rect, Qt::TextSingleLine, name);

  painter->restore();
}

QSize NewDocumentWidgetListDelegate::sizeHint(
  const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QStyleOptionViewItem opt(option);
  initStyleOption(&opt, index);

  return QSize{
    opt.rect.width(),
    m_icon_size.height() + m_margins.top() + m_margins.bottom()};
}

void NewDocumentWidgetListDelegate::setIconSize(const QSize &size)
{
  m_icon_size = size;
}

const QSize &NewDocumentWidgetListDelegate::getIconSize() const
{
  return m_icon_size;
}

void NewDocumentWidgetListDelegate::setMargins(const QMargins &margins)
{
  m_margins = margins;
}

const QMargins &NewDocumentWidgetListDelegate::getMargins() const
{
  return m_margins;
}

void NewDocumentWidgetListDelegate::setSpacing(
  int vertical_spacing, int horizontal_spacing)
{
  m_spacing.setWidth(vertical_spacing);
  m_spacing.setHeight(horizontal_spacing);
}

void NewDocumentWidgetListDelegate::setVerticalSpacing(int spacing)
{
  m_spacing.setWidth(spacing);
}

void NewDocumentWidgetListDelegate::setHorizontalSpacing(int spacing)
{
  m_spacing.setHeight(spacing);
}

int NewDocumentWidgetListDelegate::getVerticalSpacing() const
{
  return m_spacing.width();
}

int NewDocumentWidgetListDelegate::getHorizontalSpacing() const
{
  return m_spacing.height();
}
