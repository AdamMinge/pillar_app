#ifndef SHORTCUTS_TABLE_MODEL_H
#define SHORTCUTS_TABLE_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractTableModel>
#include <QAction>
/* --------------------------------- Standard ------------------------------- */
#include <utility>
/* -------------------------------------------------------------------------- */

class ShortcutsTableModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  enum Column {
    ActionColumn,
    ShortcutColumn,
    ActionIdColumn,
    ValidColumn,
    AppliedColumn,
  };

 public:
  explicit ShortcutsTableModel(QObject *parent = nullptr);
  ~ShortcutsTableModel() override;

  bool apply();
  [[nodiscard]] bool applied() const;
  [[nodiscard]] bool isValid() const;

  [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
  [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

  [[nodiscard]] QVariant data(const QModelIndex &index,
                              int role) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role) override;

  [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation,
                                    int role) const override;
  [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

 private:
  void init();
  void addedShortcut(const QString &action_id);
  void removedShortcut(const QString &action_id);

  void validation(const QSet<QKeySequence> &key_sequences);

 private:
  struct ShortcutData {
    QAction *action;
    QString action_id;
    QKeySequence key_sequence;
    bool valid;
  };

 private:
  std::vector<ShortcutData> m_actions;
};

#endif  // SHORTCUTS_TABLE_MODEL_H
