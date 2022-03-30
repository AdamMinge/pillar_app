#ifndef FLOW_PLUGIN_LIST_DELEGATE_H
#define FLOW_PLUGIN_LIST_DELEGATE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QStyledItemDelegate>
/* -------------------------------------------------------------------------- */

class PluginListDelegate : public QStyledItemDelegate
{
  Q_OBJECT

public:
  explicit PluginListDelegate(QObject *parent = nullptr);
  ~PluginListDelegate() override;

  QWidget *createEditor(
    QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(
    QWidget *editor, QAbstractItemModel *model,
    const QModelIndex &index) const override;
  void updateEditorGeometry(
    QWidget *editor, const QStyleOptionViewItem &option,
    const QModelIndex &index) const override;

  void paint(
    QPainter *painter, const QStyleOptionViewItem &option,
    const QModelIndex &index) const override;
  [[nodiscard]] QSize sizeHint(
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const override;

  void setIconSize(const QSize &size);
  [[nodiscard]] const QSize &getIconSize() const;

  void setMargins(const QMargins &margins);
  [[nodiscard]] const QMargins &getMargins() const;

  void setSpacing(int vertical_spacing, int horizontal_spacing);
  void setVerticalSpacing(int spacing);
  void setHorizontalSpacing(int spacing);

  [[nodiscard]] int getVerticalSpacing() const;
  [[nodiscard]] int getHorizontalSpacing() const;

private:
  QSize m_icon_size;
  QMargins m_margins;
  QSize m_spacing;
};

#endif//FLOW_PLUGIN_LIST_DELEGATE_H
