/* ----------------------------------- Local--------------------------------- */
#include "flow/utils/qt/stacked_widget/stacked_widget_tree_model.h"
/* -------------------------------------------------------------------------- */

namespace utils
{

  /* ------------------------- QtStackedWidgetTreeItem----------------------- */

  QtStackedWidgetTreeItem::QtStackedWidgetTreeItem(
    QString name, QWidget *widget)
      : m_parent(nullptr), m_name(std::move(name)), m_widget(widget)
  {
  }

  QtStackedWidgetTreeItem::~QtStackedWidgetTreeItem()
  {
    qDeleteAll(m_children);
  }

  QtStackedWidgetTreeItem *QtStackedWidgetTreeItem::getParent()
  {
    return m_parent;
  }

  void QtStackedWidgetTreeItem::addChild(QtStackedWidgetTreeItem *child)
  {
    if (!m_children.contains(child))
    {
      if (child->m_parent) child->m_parent->removeChild(child);

      m_children.append(child);
      child->m_parent = this;
    }
  }

  void QtStackedWidgetTreeItem::removeChild(QtStackedWidgetTreeItem *child)
  {
    if (m_children.contains(child))
    {
      m_children.removeOne(child);
      child->m_parent = nullptr;
    }
  }

  const QtStackedWidgetTreeItem *
  QtStackedWidgetTreeItem::getChild(int row) const
  {
    if (row < 0 || row >= m_children.size()) return nullptr;
    return m_children.at(row);
  }

  QtStackedWidgetTreeItem *QtStackedWidgetTreeItem::getChild(int row)
  {
    if (row < 0 || row >= m_children.size()) return nullptr;
    return m_children.at(row);
  }

  int QtStackedWidgetTreeItem::getChildCount() const
  {
    return static_cast<int>(m_children.size());
  }

  int QtStackedWidgetTreeItem::findChild(QtStackedWidgetTreeItem *child) const
  {
    return static_cast<int>(m_children.indexOf(child));
  }

  void QtStackedWidgetTreeItem::setName(QString name)
  {
    m_name = std::move(name);
  }

  void QtStackedWidgetTreeItem::setWidget(QWidget *widget)
  {
    m_widget = widget;
  }

  const QString &QtStackedWidgetTreeItem::getName() const { return m_name; }

  QWidget *QtStackedWidgetTreeItem::getWidget() const { return m_widget; }

  /* ------------------------- QtStackedWidgetTreeModel---------------------- */

  QtStackedWidgetTreeModel::QtStackedWidgetTreeModel(
    const QList<QtStackedWidgetTreeItem *> &root_items, QObject *parent)
      : QAbstractItemModel(parent), m_root_items(root_items)
  {}

  QtStackedWidgetTreeModel::~QtStackedWidgetTreeModel()
  {
    qDeleteAll(m_root_items);
  }

  Qt::ItemFlags QtStackedWidgetTreeModel::flags(const QModelIndex &index) const
  {
    return index.isValid() ? QAbstractItemModel::flags(index) : Qt::NoItemFlags;
  }

  QVariant QtStackedWidgetTreeModel::data(const QModelIndex &index,
                                          int role) const
  {
    if (index.row() < 0 || index.row() >= rowCount(QModelIndex{}))
      return QVariant{};

    auto item = static_cast<QtStackedWidgetTreeItem *>(index.internalPointer());
    switch (role)
    {
      case Qt::DisplayRole:
      case Role::NameRole:
        return item->getName();

      case Role::WidgetRole:
        return QVariant::fromValue(item->getWidget());

      default:
        return QVariant{};
    }
  }

  QVariant QtStackedWidgetTreeModel::headerData(int section,
                                                Qt::Orientation orientation,
                                                int role) const
  {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
      return QVariant{};

    switch (section)// NOLINT(hicpp-multiway-paths-covered)
    {
      case 0:
        return tr("Name");
      default:
        return QVariant{};
    }
  }

  QModelIndex QtStackedWidgetTreeModel::index(int row, int column,
                                              const QModelIndex &parent) const
  {
    if (!hasIndex(row, column, parent)) return QModelIndex{};

    QtStackedWidgetTreeItem *parent_item{nullptr};
    if (parent.isValid())
    {
      parent_item =
        static_cast<QtStackedWidgetTreeItem *>(parent.internalPointer());
      return createIndex(row, column, parent_item->getChild(row));
    } else
    {
      return createIndex(row, column, m_root_items.at(row));
    }
  }

  QModelIndex QtStackedWidgetTreeModel::parent(const QModelIndex &index) const
  {
    if (!index.isValid()) return QModelIndex{};

    auto child_item =
      static_cast<QtStackedWidgetTreeItem *>(index.internalPointer());
    auto item = child_item->getParent();

    if (m_root_items.contains(item))
    {
      auto row = static_cast<int>(m_root_items.indexOf(item));
      return createIndex(row, 0, item);
    } else
    {
      auto parent_item = item ? item->getParent() : nullptr;
      if (!parent_item) return QModelIndex{};

      auto row = parent_item->findChild(item);
      return createIndex(row, 0, item);
    }
  }

  int QtStackedWidgetTreeModel::rowCount(const QModelIndex &parent) const
  {
    if (parent.column() > 0) return 0;

    if (!parent.isValid()) return static_cast<int>(m_root_items.size());
    else
      return static_cast<QtStackedWidgetTreeItem *>(parent.internalPointer())
        ->getChildCount();
  }

  int QtStackedWidgetTreeModel::columnCount(const QModelIndex &parent) const
  {
    return 1;
  }

}// namespace utils
