/* ----------------------------------- Local -------------------------------- */
#include "flow_document/component/layers/layers_tree_delegate.h"

#include "flow_document/component/layers/layers_tree_model.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QFileInfo>
#include <QPainter>
/* -------------------------------------------------------------------------- */

namespace flow_document {

LayersTreeDelegate::LayersTreeDelegate(QObject *parent)
    : QStyledItemDelegate(parent), m_icon_size(16, 16), m_spacing(10) {}

LayersTreeDelegate::~LayersTreeDelegate() = default;

void LayersTreeDelegate::paint(QPainter *painter,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index) const {
  QStyleOptionViewItem opt(option);
  initStyleOption(&opt, index);

  auto &palette = opt.palette;
  auto &rect = opt.rect;
  auto font = QFont(opt.font);

  const auto node_name = index.data(LayersTreeModel::Role::NameRole).toString();
  const auto node_icon =
      index.data(LayersTreeModel::Role::IconRole).value<QIcon>();
  const auto actual_icon_size = node_icon.isNull() ? QSize(0, 0) : m_icon_size;
  const auto is_root_index = !index.parent().isValid();

  painter->save();

  painter->setClipping(true);
  painter->setClipRect(rect);
  painter->setFont(opt.font);

  painter->fillRect(rect, opt.state & QStyle::State_Selected
                              ? palette.highlight().color()
                              : palette.light().color());

  painter->drawPixmap(rect.left(), rect.top(),
                      node_icon.pixmap(actual_icon_size));

  auto node_name_rect =
      QFontMetrics(font).boundingRect(node_name).adjusted(0, 0, 1, 1);

  auto text_rect = rect.adjusted(
      actual_icon_size.width() + m_spacing,
      ((rect.height() / 2) - (node_name_rect.height() / 2)), 0, 0);

  font.setBold(is_root_index);

  painter->setFont(font);
  painter->setPen(palette.text().color());
  painter->drawText(text_rect, Qt::TextSingleLine, node_name);

  painter->restore();
}

QSize LayersTreeDelegate::sizeHint(const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const {
  QStyleOptionViewItem opt(option);
  initStyleOption(&opt, index);

  return QSize{opt.rect.width(),
               std::max(QFontMetrics(opt.font).height(), m_icon_size.height())};
}

}  // namespace flow_document