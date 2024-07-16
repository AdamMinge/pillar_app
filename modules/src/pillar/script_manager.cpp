/* ------------------------------------ Qt ---------------------------------- */
#include <QQmlEngine>
/* ----------------------------------- Local -------------------------------- */
#include "pillar/logging_manager.h"
#include "pillar/script_manager.h"
#include "pillar/script_module.h"
/* -------------------------------------------------------------------------- */

namespace pillar {

std::unique_ptr<ScriptManager> ScriptManager::m_instance =
    std::unique_ptr<ScriptManager>(nullptr);

ScriptManager &ScriptManager::getInstance() {
  if (!m_instance) m_instance.reset(new ScriptManager);

  return *m_instance;
}

void ScriptManager::deleteInstance() { m_instance.reset(nullptr); }

ScriptManager::ScriptManager() : m_engine(nullptr) {
  init();
  loadObjects();
}

ScriptManager::~ScriptManager() = default;

QJSValue ScriptManager::evaluate(const QString &program,
                                 const QString &file_name, int line) {
  auto result = m_engine->evaluate(program, file_name, line);
  const auto errorMessage = getErrorMessage(result, program);
  if (!errorMessage.isEmpty()) LOG_ERROR(errorMessage);

  return result;
}

void ScriptManager::reset() {
  m_engine.reset();

  init();
}

void ScriptManager::init() {
  if (!m_engine) {
    m_engine = std::make_unique<QQmlEngine>();

    m_engine->setOutputWarningsToStandardError(false);
    connect(m_engine.get(), &QQmlEngine::warnings, this,
            &ScriptManager::onScriptWarnings);
  }
}

QString ScriptManager::getErrorMessage(const QJSValue &value,
                                       const QString &program) const {
  if (!value.isError()) return QString{};

  auto errorString = value.toString();
  auto stack = value.property(QStringLiteral("stack")).toString();

  const auto stackEntries = QStringView(stack).split(QLatin1Char('\n'));
  if (!stackEntries.empty() &&
      !stackEntries.first().startsWith(QLatin1String("%entry@"))) {
    errorString.append(QLatin1Char('\n'));
    errorString.append(tr("Stack traceback:"));
    errorString.append(QLatin1Char('\n'));

    for (const auto &entry : stackEntries) {
      errorString.append(QStringLiteral("  "));
      errorString.append(entry);
      errorString.append(QLatin1Char('\n'));
    }

    errorString.chop(1);
  } else if (program.isEmpty() || program.contains(QLatin1Char('\n'))) {
    errorString = tr("At line %1: %2")
                      .arg(value.property(QStringLiteral("lineNumber")).toInt())
                      .arg(errorString);
  }

  return errorString;
}

void ScriptManager::addedObject(ScriptModule *script_module) {
  auto global_object = m_engine->globalObject();
  global_object.setProperty(script_module->getName(),
                            m_engine->newQObject(script_module));
}

void ScriptManager::removedObject(ScriptModule *script_module) {
  auto global_object = m_engine->globalObject();
  global_object.deleteProperty(script_module->getName());
}

void ScriptManager::onScriptWarnings(const QList<QQmlError> &warnings) {
  for (const auto &warning : warnings) {
    LOG_ERROR(warning.toString());
  }
}

}  // namespace pillar
