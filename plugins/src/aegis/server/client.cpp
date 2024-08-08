/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/client.h"

#include "aegis/server/command/executor.h"
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
      m_command_manager(std::make_unique<CommandExecutor>()) {
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
  const auto response = m_command_manager->exec(data);

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
