#include "manager.h"

#include "ledstate.h"
#include "protocol.h"

#include <QtNetwork>

Manager::Manager(QObject *_parent)
    : QObject(_parent)
    , m_emulator(new DeviceEmulator(90, 0, 5))
    , tcpServer(new QTcpServer(this))
    , clientsConnected(0)
{
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(registerSocket()));
}

void Manager::launchServer()
{
    if (!tcpServer->listen()) {
        Q_EMIT message(tr("Unable to start the server: %1.")
                       .arg(tcpServer->errorString()));
        reportStatus();
        return;
    }
    clientsConnected = 0;
    reportStatus();
    Q_EMIT message(tr("Server started. Run the Client example now."));
}

void Manager::registerSocket()
{
    ++clientsConnected;
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    reportStatus();
    Q_EMIT message(tr("Client %1(%2) connected.")
                   .arg(clientConnection->peerAddress().toString())
                   .arg(clientConnection->peerPort()));
    connect(clientConnection, SIGNAL(disconnected()),
            this, SLOT(clearSocket()));
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readRequest()));
    connect(clientConnection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
}

void Manager::readRequest()
{
    QTcpSocket *clientConnection = qobject_cast<QTcpSocket *>(sender());
    if(!clientConnection)
        return;

    QDataStream in(clientConnection);
    in.setVersion(QDataStream::Qt_4_0);

    QString requestString;
    in >> requestString;

    Q_EMIT message("Request received: " + requestString);

    QString response = processCommand(requestString);

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << response;
    out.device()->seek(0);

    Q_EMIT message("Submit response: " + response);

    clientConnection->write(block);
}

void Manager::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        Q_EMIT message(tr("The host was not found. Please check the "
                                "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        Q_EMIT message(tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default: {
        QTcpSocket *clientConnection = qobject_cast<QTcpSocket *>(sender());
        if(!clientConnection) {
            Q_EMIT message(tr("The error occurred."));
            return;
        }
        Q_EMIT message(tr("The following error occurred: %1.")
                                 .arg(clientConnection->errorString()));
        break;
    }
    }
}

void Manager::clearSocket()
{
    QTcpSocket *clientConnection = qobject_cast<QTcpSocket *>(sender());
    if(!clientConnection)
        return;
    --clientsConnected;
    reportStatus();
    Q_EMIT message(tr("Client disconnected."));
    clientConnection->deleteLater();
}

QString Manager::processCommand(const QString &_command)
{
    Protocol protocol;
    QString result = protocol.response2Str(false, MaxCommand);
    if(!m_emulator->deviceEnabled()) {
        return result;
    }
    bool ok;
    ECommand command = protocol.str2Request(_command, &ok);
    if(!ok) {
        return result;
    }
    switch(command) {
    case SetLedState: {
        m_emulator->setStateOn(protocol.on());
        break;
    }
    case GetLedState: {
        protocol.setStateOn(m_emulator->stateOn());
        break;
    }
    case SetLedColor: {
        m_emulator->setColor(protocol.color());
        break;
    }
    case GetLedColor: {
        protocol.setColor(m_emulator->color());
        break;
    }
    case SetLedRate: {
        if(!m_emulator->setRate(protocol.rate())) {
            return result;
        }
        break;
    }
    case GetLedRate: {
        protocol.setRate(m_emulator->rate());
        break;
    }
    default: {
        break;
    }
    }
    return protocol.response2Str(true, command);
}

void Manager::reportStatus()
{
    if(tcpServer->isListening()) {
        Q_EMIT statusChanged(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                                "%3 clients connected.")
                             .arg(serverAddress())
                             .arg(tcpServer->serverPort()).arg(clientsConnected));
    } else {
        Q_EMIT statusChanged(tr("Server not running."));
    }
}

QString Manager::serverAddress() const
{
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    return ipAddress;
}
