#ifndef PLUGIN_LIST_MODEL_H
#define PLUGIN_LIST_MODEL_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractListModel>
/* --------------------------------- Standard ------------------------------- */
#include <utility>
/* -------------------------------------------------------------------------- */

namespace egnite {
class Plugin;
}

class PluginListModel : public QAbstractListModel {
  Q_OBJECT

 public:
  enum Role {
    PluginName = Qt::UserRole + 1,
    PluginDescription,
    PluginVersion,
    PluginIcon,
    PluginFileNameRole,
    PluginStateRole,
  };

 public:
  explicit PluginListModel(QObject *parent = nullptr);
  ~PluginListModel() override;

  bool apply();
  [[nodiscard]] bool applied() const;

  bool setData(const QModelIndex &index, const QVariant &value,
               int role) override;
  [[nodiscard]] QVariant data(const QModelIndex &index,
                              int role) const override;

  [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;
  [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

 Q_SIGNALS:
  void appliedChanged(bool applied);

 protected:
  QVector<std::pair<egnite::Plugin *, bool>> m_plugins;
};

class StaticPluginListModel : public PluginListModel {
  Q_OBJECT

 public:
  explicit StaticPluginListModel(QObject *parent = nullptr);
  ~StaticPluginListModel() override;
};

class DynamicPluginListModel : public PluginListModel {
  Q_OBJECT

 public:
  explicit DynamicPluginListModel(QObject *parent = nullptr);
  ~DynamicPluginListModel() override;
};

#endif  // PLUGIN_LIST_MODEL_H
