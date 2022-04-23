#ifndef FLOW_STACKED_WIDGET_TREE_MODEL_H
#define FLOW_STACKED_WIDGET_TREE_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemModel>
#include <QWidget>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qt/stacked_widget/export.h"
/* -------------------------------------------------------------------------- */

namespace utils
{

  class STACKED_WIDGET_API QtStackedWidgetTreeItem
  {
  public:
    explicit QtStackedWidgetTreeItem(
      QWidget *widget,
      std::initializer_list<QtStackedWidgetTreeItem *> children = {});
    ~QtStackedWidgetTreeItem();

    [[nodiscard]] QtStackedWidgetTreeItem *getParent();

    void addChild(QtStackedWidgetTreeItem *child);
    void removeChild(QtStackedWidgetTreeItem *child);

    [[nodiscard]] const QtStackedWidgetTreeItem *getChild(int row) const;
    [[nodiscard]] QtStackedWidgetTreeItem *getChild(int row);
    [[nodiscard]] int getChildCount() const;
    [[nodiscard]] int findChild(QtStackedWidgetTreeItem *child) const;

    void setWidget(QWidget *widget);
    [[nodiscard]] QWidget *getWidget() const;

  private:
    QList<QtStackedWidgetTreeItem *> m_children;
    QtStackedWidgetTreeItem *m_parent;
    QWidget *m_widget;
  };

  class STACKED_WIDGET_API QtStackedWidgetTreeModel : public QAbstractItemModel
  {
    Q_OBJECT

  public:
    enum Role
    {
      NameRole = Qt::UserRole + 1,
      WidgetRole,
      ObjectNameRole
    };

  public:
    [[nodiscard]] static QModelIndex getIndexBy(
      const QAbstractItemModel &model, Role role, const QVariant &value,
      const QModelIndex &parent);

  public:
    explicit QtStackedWidgetTreeModel(QObject *parent = nullptr);
    ~QtStackedWidgetTreeModel() override;

    void append(QtStackedWidgetTreeItem *item, const QModelIndex &parent);
    void remove(const QModelIndex &index);

    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

    [[nodiscard]] QVariant
    data(const QModelIndex &index, int role) const override;
    [[nodiscard]] QVariant headerData(
      int section, Qt::Orientation orientation, int role) const override;

    [[nodiscard]] QModelIndex
    index(int row, int column, const QModelIndex &parent) const override;
    [[nodiscard]] QModelIndex parent(const QModelIndex &index) const override;

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
    [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

    [[nodiscard]] QModelIndex
    getIndexBy(Role role, const QVariant &value, const QModelIndex &parent) const;

  private:
    QList<QtStackedWidgetTreeItem *> m_root_items;
  };

}// namespace utils

#endif//FLOW_STACKED_WIDGET_TREE_MODEL_H
