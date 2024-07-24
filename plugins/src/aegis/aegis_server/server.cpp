/* ----------------------------------- Local -------------------------------- */
#include "aegis_server/server.h"

#include "aegis_server/client.h"
/* -------------------------------------------------------------------------- */

namespace aegis_server {

Server::Server(QObject* parent) : QTcpServer(parent) {}

Server::~Server() { stop(); }

bool Server::start(const QHostAddress& host, quint16 port) {
  return QTcpServer::listen(host, port);
}

void Server::stop() {
  if (!QTcpServer::isListening()) return;

  for (auto thread : m_threads) {
    thread->quit();
    thread->wait();
  }
  m_threads.clear();

  QTcpServer::close();
}

void Server::incomingConnection(qintptr socket_descriptor) {
  ClientThread* thread = new ClientThread(socket_descriptor);

  connect(thread, &ClientThread::destroyed, thread,
          [this](auto object) { m_threads.removeAll(object); });

  m_threads.append(thread);
  thread->start();
}

}  // namespace aegis_server
