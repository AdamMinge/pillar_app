/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/client.h"

#include "aegis/server/command/command.h"
#include "aegis/server/response.h"
#include "aegis/server/serializer.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QMutexLocker>
/* -------------------------------------------------------------------------- */

namespace aegis {

/* -------------------------------- ClientThread ---------------------------- */

ClientThread::ClientThread(qintptr socket_descriptor, QObject* parent)
    : QThread(parent), m_socket_descriptor(socket_descriptor) {}

ClientThread::~ClientThread() = default;

void ClientThread::run() {
  ClientHandler* handler = new ClientHandler(m_socket_descriptor);

  connect(handler, &ClientHandler::finished, this, &ClientThread::quit);
  connect(this, &QThread::finished, handler, &ClientHandler::deleteLater);
  connect(this, &QThread::finished, this, &ClientThread::deleteLater);

  exec();
}

/* ----------------------------------- Client ------------------------------- */

ClientHandler::ClientHandler(qintptr socket_descriptor, QObject* parent)
    : QObject(parent),
      m_socket(std::make_unique<QTcpSocket>()),
      m_serializer(std::make_unique<ResponseSerializer>(
          ResponseSerializer::Format::Json)) {
  if (!m_socket->setSocketDescriptor(socket_descriptor)) {
    emit error(m_socket->error());
    return;
  }

  connect(m_socket.get(), &QTcpSocket::readyRead, this,
          &ClientHandler::readyRead);
  connect(m_socket.get(), &QTcpSocket::disconnected, this,
          &ClientHandler::disconnected);
}

ClientHandler::~ClientHandler() = default;

void ClientHandler::readyRead() {
  const auto data = m_socket->readAll();
  const auto splited_data = data.split(' ');
  const auto command_name = splited_data.front();

  auto response = QByteArray{};
  if (auto iter = m_commands.find(command_name); iter != m_commands.end()) {
    auto args = QStringList{};
    std::transform(splited_data.constBegin(), splited_data.constEnd(),
                   std::back_inserter(args),
                   [](const auto& data) { return QString::fromUtf8(data); });

    response = (*iter).second->exec(args);
  } else {
    auto error = Response<>(ErrorMessage(
        QLatin1String("Process Request Error"),
        QLatin1String("Cannot find command: %1").arg(command_name)));
    response = m_serializer->serialize(error);
  }

  if (!response.isEmpty()) {
    m_socket->write(response);
    m_socket->flush();
  }
}

void ClientHandler::disconnected() {
  m_socket->close();
  emit finished();
}

}  // namespace aegis
