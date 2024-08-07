/* ----------------------------------- Local -------------------------------- */
#include "aegis/server/server.h"

#include "aegis/server/client.h"
/* -------------------------------------------------------------------------- */

namespace aegis {

Server::Server(QObject* parent) : QTcpServer(parent) {}

Server::~Server() { close(); }

void Server::close() {
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

}  // namespace aegis
