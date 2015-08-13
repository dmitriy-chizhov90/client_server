#include "manager.h"

Manager::Manager(QObject *_parent)
    : QObject(_parent)
    , m_tcpSocket(new QTcpSocket(this))
    , m_status(tr("Disconnected"))
    , m_currentCommand(MaxCommand)
{
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(readFromSocket()));
    connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void Manager::updateState()
{
    m_commands.clear();
    m_commands << GetLedState << GetLedColor << GetLedRate;
    executeCommands();
}

void Manager::submitState(const LedState &_state)
{
    m_state = _state;
    m_commands.clear();
    m_commands << SetLedState << SetLedColor << SetLedRate;
    executeCommands();
}

void Manager::setStatus(const QString &_status)
{
    m_status = _status;
    Q_EMIT statusChanged();
}

bool Manager::connected() const
{
    return (m_tcpSocket->state() == QAbstractSocket::ConnectedState);
}

void Manager::connectToServer(const QString &_host, int _port)
{
    disconnectFromServer();
    Q_EMIT message(QString(tr("Attempting connect to host %1 (%2).")).arg(_host).arg(_port));
    m_tcpSocket->connectToHost(_host, _port);
    if(m_tcpSocket->waitForConnected()) {
        Q_EMIT message(QString(tr("Connected to host %1 (%2).")).arg(_host).arg(_port));
        setStatus(tr("Connected"));
    } else {
        Q_EMIT message(tr("Connect failed."));
    }
}

void Manager::disconnectFromServer()
{
    if(connected()) {
        m_tcpSocket->abort();
    }
}

void Manager::readFromSocket()
{
    QDataStream in(m_tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    QString response;
    in >> response;

    Q_EMIT message(tr("Response received: ") + response);

    Protocol protocol;
    bool ok = false;
    bool result = protocol.str2Response(response, m_currentCommand, &ok);
    if(!ok) {
        Q_EMIT message("Failed to parse response.");
    } else if(!result) {
        Q_EMIT message("Device cannot execute request.");
    } else {
        switch(m_currentCommand) {
        case SetLedState:
        case SetLedColor:
        case SetLedRate: {
            Q_EMIT message("Device has changed it's state successful.");
            break;
        }
        case GetLedState: {
            Q_EMIT message("Device state received successful.");
            m_state.on = protocol.on();
            Q_EMIT stateChanged();
            break;
        }
        case GetLedColor: {
            Q_EMIT message("Device color received successful.");
            m_state.color = protocol.color();
            Q_EMIT stateChanged();
            break;
        }
        case GetLedRate: {
            Q_EMIT message("Device rate received successful.");
            m_state.rate = protocol.rate();
            Q_EMIT stateChanged();
            break;
        }
        default: {
            break;
        }
        }
    }
    executeCommands();
}

void Manager::displayError(QAbstractSocket::SocketError _socketError)
{
    Q_EMIT displayError(_socketError, m_tcpSocket->errorString());
}

void Manager::disconnected()
{
    setStatus(tr("Disconnected"));
    Q_EMIT message(tr("Disconnected."));
}

void Manager::executeCommands()
{
    m_currentCommand = MaxCommand;
    if(m_commands.isEmpty()) {
        return;
    }
    m_currentCommand = m_commands.takeFirst();
    Protocol protocol;
    protocol.setStateOn(m_state.on);
    protocol.setColor(m_state.color);
    protocol.setRate(m_state.rate);

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    QString request = protocol.request2Str(m_currentCommand);
    out << request;

    Q_EMIT message(tr("Attempt sending request: ") + request);

    m_tcpSocket->write(block);
    if(m_tcpSocket->waitForBytesWritten()) {
        Q_EMIT message(tr("Send successeful."));
    } else {
        Q_EMIT message(tr("Send failed."));
    }
}
