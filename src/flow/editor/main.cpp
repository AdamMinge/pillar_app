/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QCommandLineParser>
/* ----------------------------------- Local -------------------------------- */
#include "flow/config.h"
#include "flow/editor/document/flow/flow_document_format_flow.h"
#include "flow/editor/main_window.h"
#include "flow/editor/plugin_manager.h"
#include "flow/editor/project/project_format_pro.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------- messagesToConsole -------------------------- */

static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER =
  qInstallMessageHandler(nullptr);// NOLINT(cert-err58-cpp)

static void messagesToConsole(
  QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
  switch (type)
  {
    case QtInfoMsg:
    case QtDebugMsg:
      // TODO : implementation //
      break;

    case QtWarningMsg:
      // TODO : implementation //
      break;

    case QtCriticalMsg:
      // TODO : implementation //
      break;

    default:
      break;
  }

  (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
}

/* ----------------------------- CommandLineParser -------------------------- */

class CommandLineParser
{
public:
  explicit CommandLineParser();
  ~CommandLineParser() = default;

  void process(const QCoreApplication &app);
};

CommandLineParser::CommandLineParser() = default;

void CommandLineParser::process(const QCoreApplication &app)
{
  QCommandLineParser parser;
  parser.setApplicationDescription("Flow Editor");
  parser.addHelpOption();
  parser.addVersionOption();

  parser.process(app);
}

/* -------------------------- RegisterDefaultPlugins ------------------------ */

static void registerDefaultPlugins(QApplication &app)
{
  auto project_default_format = new ProjectFormatPro(&app);
  auto flow_document_default_format = new FlowDocumentFormatFlow(&app);

  PluginManager::getInstance().addObject(project_default_format);
  PluginManager::getInstance().addObject(flow_document_default_format);
}

/* ----------------------------------- main --------------------------------- */

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QApplication::setApplicationName(QStringLiteral("Flow-Editor"));
  QApplication::setApplicationVersion(QLatin1String(FLOW_VERSION_STR));
  QApplication::setApplicationDisplayName(QStringLiteral("Flow-Editor"));
  QApplication::setOrganizationName(QStringLiteral("Flow"));

  qInstallMessageHandler(messagesToConsole);

  CommandLineParser parser;
  parser.process(app);

  registerDefaultPlugins(app);

  MainWindow mainWindow;
  mainWindow.show();

  return QApplication::exec();
}
