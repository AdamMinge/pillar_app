#ifndef FLOW_SCRIPT_MANAGER_H
#define FLOW_SCRIPT_MANAGER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QScopedPointer>
#include <QtQml/QJSEngine>
#include <QtQml/QQmlError>
/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
/* -------------------------------------------------------------------------- */

namespace flow
{

  class ScriptModule;

  class LIB_FLOW_API ScriptManager : public QObject
  {
    Q_OBJECT

  public:
    [[nodiscard]] static ScriptManager &getInstance();
    static void deleteInstance();

  public:
    ~ScriptManager() override;

    QJSValue evaluate(
      const QString &program, const QString &file_name = QString(),
      int line = 1);

  private:
    explicit ScriptManager();

    void reset();
    void init();

    [[nodiscard]] QString
    getErrorMessage(const QJSValue &value, const QString &program) const;

  private Q_SLOTS:
    void onScriptWarnings(const QList<QQmlError> &warnings);

  private:
    static QScopedPointer<ScriptManager> m_instance;

    std::unique_ptr<QJSEngine> m_engine;
    std::unique_ptr<ScriptModule> m_script_module;
  };

}// namespace flow

#endif//FLOW_SCRIPT_MANAGER_H
