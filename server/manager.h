#ifndef MANAGER_H
#define MANAGER_H

#include "deviceemulator.h"

#include <QScopedPointer>
#include <QTcpSocket>
#include <QObject>

class QTcpServer;
// ����� ��������� ������� �� ������� � �����������
class Manager : public QObject
{
    Q_OBJECT
public:
    Manager(QObject *_parent = 0);
    // ������ �������
    void launchServer();

Q_SIGNALS:
    // ���������
    void message(const QString &_msg);
    // ��������� �������
    void statusChanged(const QString &_status);

private Q_SLOTS:
    // ����������� ������ �����������
    void registerSocket();
    // ������ �������
    void readRequest();
    // ��������� ������
    void displayError(QAbstractSocket::SocketError socketError);
    // ������� ����������
    void clearSocket();

private:
    // ����������
    QScopedPointer<DeviceEmulator> m_emulator;
    // ������
    QTcpServer *tcpServer;
    // ���������� ����������� ��������
    int clientsConnected;

    // ��������� �������
    QString processCommand(const QString &_command);
    // ����� � �������
    void reportStatus();
    // ����� �������
    QString serverAddress() const;
};

#endif // MANAGER_H
