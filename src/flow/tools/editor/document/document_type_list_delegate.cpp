/* ------------------------------------ Qt ---------------------------------- */
#include <QPainter>
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "flow/tools/editor/document/document_type_list_delegate.h"
#include "flow/tools/editor/document/document_type_list_model.h"
/* -------------------------------------------------------------------------- */

DocumentTypeListDelegate::DocumentTypeListDelegate(QObject* parent) :
  QStyledItemDelegate(parent),
  m_icon_size(64, 64),
  m_margins(0, 0, 0, 0),
  m_spacing(0, 0)
{

}

DocumentTypeListDelegate::~DocumentTypeListDelegate() = default;

void DocumentTypeListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QStyleOptionViewItem opt(option);
  initStyleOption(&opt, index);

  auto& palette = opt.palette;
  auto& rect = opt.rect;
  auto font = QFont(opt.font);
  auto content_rect = rect.adjusted(m_margins.left(), m_margins.top(),
                                    -m_margins.right(), -m_margins.bottom());

  auto is_last_index = index.model()->rowCount() - 1 == index.row();
  auto name = index.data(DocumentTypeListModel::Role::DocumentTypeNameRole).toString();

  painter->save();

  painter->setClipping(true);
  painter->setClipRect(rect);
  painter->setFont(opt.font);

  painter->fillRect(rect,opt.state & QStyle::State_Selected ?
                    palette.highlight().color() : palette.light().color());

  painter->drawLine(is_last_index ? rect.left() : content_rect.left(),
                    rect.bottom(), rect.right(), rect.bottom());

  painter->drawPixmap(content_rect.left(), content_rect.top(),
                      index.data(DocumentTypeListModel::Role::DocumentTypeIconRole).value<QIcon>().pixmap(m_icon_size));

  auto text_rect = content_rect.adjusted(
      m_icon_size.width() + m_spacing.width(),
      static_cast<int>((content_rect.top() + m_icon_size.height() - opt.font.pointSize() * 1.4) / 2),
      0, 0);

  font.setPointSizeF(opt.font.pointSize() * 1.4);
  painter->setFont(font);
  painter->setPen(palette.text().color());
  painter->drawText(text_rect, Qt::TextSingleLine, name);

  painter->restore();
}

QSize DocumentTypeListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QStyleOptionViewItem opt(option);
  initStyleOption(&opt, index);

  return QSize{opt.rect.width(),  m_icon_size.height() + m_margins.top() + m_margins.bottom()};
}

void DocumentTypeListDelegate::setIconSize(const QSize& size)
{
  m_icon_size = size;
}

const QSize& DocumentTypeListDelegate::getIconSize() const
{
  return m_icon_size;
}

void DocumentTypeListDelegate::setMargins(const QMargins& margins)
{
  m_margins = margins;
}

const QMargins& DocumentTypeListDelegate::getMargins() const
{
  return m_margins;
}

void DocumentTypeListDelegate::setSpacing(int vertical_spacing, int horizontal_spacing)
{
  m_spacing.setWidth(vertical_spacing);
  m_spacing.setHeight(horizontal_spacing);
}

void DocumentTypeListDelegate::setVerticalSpacing(int spacing)
{
  m_spacing.setWidth(spacing);
}

void DocumentTypeListDelegate::setHorizontalSpacing(int spacing)
{
  m_spacing.setHeight(spacing);
}

int DocumentTypeListDelegate::getVerticalSpacing() const
{
  return m_spacing.width();
}

int DocumentTypeListDelegate::getHorizontalSpacing() const
{
  return m_spacing.height();
}
