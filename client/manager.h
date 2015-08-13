#ifndef MANAGER_H
#define MANAGER_H

#include <QStringList>
#include <QTcpSocket>
#include <QObject>

#include "ledstate.h"
#include "protocol.h"

// ����� �������� � �������� ��������� �� ����
class Manager : public QObject
{
    Q_OBJECT
public:
    Manager(QObject *_parent = 0);
    // ��������� ����������
    LedState state() const { return m_state; }
    // �������� ���������
    void updateState();
    // ��������� ���������
    void submitState(const LedState &_state);
    // ������ ���������
    QString status() const { return m_status; }
    // �������� ����������
    bool connected() const;

public Q_SLOTS:
    // ����������� � ��������
    void connectToServer(const QString &_host, int _port);
    // ��������� ����������
    void disconnectFromServer();

Q_SIGNALS:
    // ��������� ���������� ����������
    void stateChanged();
    // ������ ���������
    void statusChanged();
    // ���������
    void message(const QString &_msg);
    // ��������� �� ������
    void displayError(QAbstractSocket::SocketError, const QString &);

private Q_SLOTS:
    // ������ ��������� �� ����
    void readFromSocket();
    // ��������� ������
    void displayError(QAbstractSocket::SocketError _socketError);
    // ��������� ������� ����������
    void disconnected();

private:
    QTcpSocket *m_tcpSocket;
    // ������
    QString m_status;
    // ��������� ����������
    LedState m_state;
    // ������� �������
    ECommand m_currentCommand;
    // ������� ������
    QList<ECommand> m_commands;

    // ���������� ������
    void setStatus(const QString &_status);
    // ��������� ������� �� �������
    void executeCommands();
};

#endif // MANAGER_H
