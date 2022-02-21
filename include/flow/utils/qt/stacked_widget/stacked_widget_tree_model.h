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
      QString name, QWidget *widget,
      std::initializer_list<QtStackedWidgetTreeItem *> children = {});
    ~QtStackedWidgetTreeItem();

    [[nodiscard]] QtStackedWidgetTreeItem *getParent();

    void addChild(QtStackedWidgetTreeItem *child);
    void removeChild(QtStackedWidgetTreeItem *child);

    [[nodiscard]] const QtStackedWidgetTreeItem *getChild(int row) const;
    [[nodiscard]] QtStackedWidgetTreeItem *getChild(int row);
    [[nodiscard]] int getChildCount() const;
    [[nodiscard]] int findChild(QtStackedWidgetTreeItem *child) const;

    void setName(QString name);
    void setWidget(QWidget *widget);

    [[nodiscard]] const QString &getName() const;
    [[nodiscard]] QWidget *getWidget() const;

  private:
    QList<QtStackedWidgetTreeItem *> m_children;
    QtStackedWidgetTreeItem *m_parent;

    QString m_name;
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
    };

  public:
    explicit QtStackedWidgetTreeModel(
      const QList<QtStackedWidgetTreeItem *> &root_items,
      QObject *parent = nullptr);
    ~QtStackedWidgetTreeModel() override;

    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index,
                                int role) const override;
    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation,
                                      int role) const override;

    [[nodiscard]] QModelIndex index(int row, int column,
                                    const QModelIndex &parent) const override;
    [[nodiscard]] QModelIndex parent(const QModelIndex &index) const override;

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
    [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

  private:
    QList<QtStackedWidgetTreeItem *> m_root_items;
  };

}// namespace utils

#endif//FLOW_STACKED_WIDGET_TREE_MODEL_H
