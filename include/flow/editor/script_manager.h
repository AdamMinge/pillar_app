#ifndef FLOW_SCRIPT_MANAGER_H
#define FLOW_SCRIPT_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QJSEngine>
#include <QObject>
#include <QQmlError>
#include <QScopedPointer>
/* -------------------------------------------------------------------------- */

class ScriptModule;

class ScriptManager : public QObject
{
  Q_OBJECT

public:
  [[nodiscard]] static ScriptManager &getInstance();
  static void deleteInstance();

public:
  ~ScriptManager() override;

  QJSValue evaluate(
    const QString &program, const QString &file_name = QString(), int line = 1);

private:
  explicit ScriptManager();

  void reset();
  void init();

  bool checkError(const QJSValue &value, const QString &program) const;

private Q_SLOTS:
  void onScriptWarnings(const QList<QQmlError> &warnings);

private:
  static QScopedPointer<ScriptManager> m_instance;

  std::unique_ptr<QJSEngine> m_engine;
  std::unique_ptr<ScriptModule> m_script_module;
};

#endif//FLOW_SCRIPT_MANAGER_H
