/* ------------------------------------ Qt ---------------------------------- */
#include <QQmlEngine>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/logging_manager.h"
#include "flow/editor/script_manager.h"
#include "flow/editor/script_module.h"
/* -------------------------------------------------------------------------- */

QScopedPointer<ScriptManager> ScriptManager::m_instance =
  QScopedPointer<ScriptManager>(nullptr);

ScriptManager &ScriptManager::getInstance()
{
  if (m_instance.isNull()) m_instance.reset(new ScriptManager);

  return *m_instance;
}

void ScriptManager::deleteInstance() { m_instance.reset(nullptr); }

ScriptManager::ScriptManager() : m_engine(nullptr), m_script_module(nullptr)
{
  init();
}

ScriptManager::~ScriptManager() = default;

QJSValue ScriptManager::evaluate(
  const QString &program, const QString &file_name, int line)
{
  auto result = m_engine->evaluate(program, file_name, line);
  const auto errorMessage = getErrorMessage(result, program);
  if (!errorMessage.isEmpty()) LOG_ERROR(errorMessage);

  return result;
}

void ScriptManager::reset()
{
  m_engine.reset();
  m_script_module.reset();

  init();
}

void ScriptManager::init()
{
  if (!m_engine)
  {
    auto engine = std::make_unique<QQmlEngine>();
    auto script_module = std::make_unique<ScriptModule>();

    engine->setOutputWarningsToStandardError(false);
    connect(
      engine.get(), &QQmlEngine::warnings, this,
      &ScriptManager::onScriptWarnings);

    auto global_object = engine->globalObject();
    global_object.setProperty(
      QStringLiteral("Flow"), engine->newQObject(script_module.get()));

    m_engine = std::move(engine);
    m_script_module = std::move(script_module);
  }
}

QString ScriptManager::getErrorMessage(
  const QJSValue &value, const QString &program) const
{
  if (!value.isError()) return QString{};

  auto errorString = value.toString();
  auto stack = value.property(QStringLiteral("stack")).toString();

  const auto stackEntries = QStringView(stack).split(QLatin1Char('\n'));
  if (
    !stackEntries.empty() &&
    !stackEntries.first().startsWith(QLatin1String("%entry@")))
  {
    errorString.append(QLatin1Char('\n'));
    errorString.append(tr("Stack traceback:"));
    errorString.append(QLatin1Char('\n'));

    for (const auto &entry : stackEntries)
    {
      errorString.append(QStringLiteral("  "));
      errorString.append(entry);
      errorString.append(QLatin1Char('\n'));
    }

    errorString.chop(1);
  } else if (program.isEmpty() || program.contains(QLatin1Char('\n')))
  {
    errorString = tr("At line %1: %2")
                    .arg(value.property(QStringLiteral("lineNumber")).toInt())
                    .arg(errorString);
  }

  return errorString;
}

void ScriptManager::onScriptWarnings(const QList<QQmlError> &warnings)
{
  for (const auto &warning : warnings) { LOG_ERROR(warning.toString()); }
}
