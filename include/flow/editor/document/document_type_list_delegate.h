#ifndef FLOW_DOCUMENT_TYPE_LIST_DELEGATE_H
#define FLOW_DOCUMENT_TYPE_LIST_DELEGATE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QStyledItemDelegate>
/* -------------------------------------------------------------------------- */

class DocumentTypeListDelegate : public QStyledItemDelegate
{
  Q_OBJECT

public:
  explicit DocumentTypeListDelegate(QObject *parent = nullptr);
  ~DocumentTypeListDelegate() override;

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const override;
  [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option,
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

#endif//FLOW_DOCUMENT_TYPE_LIST_DELEGATE_H
