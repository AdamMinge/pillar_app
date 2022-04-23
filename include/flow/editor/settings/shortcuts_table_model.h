#ifndef FLOW_SHORTCUTS_TABLE_MODEL_H
#define FLOW_SHORTCUTS_TABLE_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractTableModel>
#include <QAction>
/* --------------------------------- Standard ------------------------------- */
#include <utility>
/* -------------------------------------------------------------------------- */

class ShortcutsTableModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  enum Column
  {
    ActionColumn,
    ShortcutColumn,
    ActionIdColumn
  };

public:
  explicit ShortcutsTableModel(QObject *parent = nullptr);
  ~ShortcutsTableModel() override;

  bool apply();
  [[nodiscard]] bool applied() const;

  [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
  [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

  [[nodiscard]] QVariant
  data(const QModelIndex &index, int role) const override;
  bool
  setData(const QModelIndex &index, const QVariant &value, int role) override;

  [[nodiscard]] QVariant
  headerData(int section, Qt::Orientation orientation, int role) const override;
  [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
  void init();
  void addedShortcut(const QString& action_id);
  void removedShortcut(const QString& action_id);

Q_SIGNALS:
  void appliedChanged(bool applied);

private:
  struct ShortcutData {
    QAction *action;
    QString action_id;
    QKeySequence key_sequence;
  };

private:
  std::vector<ShortcutData> m_actions;
};

#endif//FLOW_SHORTCUTS_TABLE_MODEL_H
