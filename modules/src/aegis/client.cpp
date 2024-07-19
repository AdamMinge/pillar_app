/* ----------------------------------- Local -------------------------------- */
#include "aegis/client.h"

#include "aegis/command/recorder.h"
#include "aegis/command/response.h"
#include "aegis/serializer.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QJsonDocument>
/* -------------------------------------------------------------------------- */

namespace aegis {

Client::Client(qintptr socket_descriptor)
    : m_socket_descriptor(socket_descriptor),
      m_serializer(std::make_unique<Serializer>(Serializer::Format::Json)) {
  initCommands();
  setAutoDelete(true);
}

void Client::run() {
  m_socket = std::make_unique<QTcpSocket>();
  if (!m_socket->setSocketDescriptor(m_socket_descriptor)) {
    return;
  }

  while (m_socket->state() == QAbstractSocket::ConnectedState) {
    if (m_socket->waitForReadyRead(3000)) {
      const auto data = m_socket->readAll();
      processRequest(data);
    }
  }

  m_socket->disconnectFromHost();
  m_socket->waitForDisconnected();
}

void Client::initCommands() {
  m_commands.insert(
      std::make_pair(RecorderCommand::name(),
                     std::make_unique<RecorderCommand>(*m_serializer)));
}

void Client::processRequest(const QByteArray& data) {
  auto splited_data = data.split(' ');
  auto command_name = splited_data.front();

  if (auto iter = m_commands.find(command_name); iter != m_commands.end()) {
    auto args = QStringList{};
    std::transform(splited_data.constBegin(), splited_data.constEnd(),
                   std::back_inserter(args),
                   [](const auto& data) { return QString::fromUtf8(data); });

    auto response = (*iter).second->exec(args);
    sendResponse(response);
  } else {
    auto error = ErrorResponse(
        QLatin1String("Process Request Error"),
        QLatin1String("Cannot find command: %1").arg(command_name));
    auto response = m_serializer->serialize(error);
    sendResponse(response);
  }
}

void Client::sendResponse(const QByteArray& data) {
  m_socket->write(data);
  m_socket->flush();
}

}  // namespace aegis
