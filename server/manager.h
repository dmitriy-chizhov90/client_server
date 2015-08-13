#ifndef MANAGER_H
#define MANAGER_H

#include "deviceemulator.h"

#include <QScopedPointer>
#include <QTcpSocket>
#include <QObject>

class QTcpServer;
// Класс связывает запросы от сервера с устройством
class Manager : public QObject
{
    Q_OBJECT
public:
    Manager(QObject *_parent = 0);
    // Запуск сервера
    void launchServer();

Q_SIGNALS:
    // Сообщение
    void message(const QString &_msg);
    // Изменение статуса
    void statusChanged(const QString &_status);

private Q_SLOTS:
    // Регистрация нового соединениея
    void registerSocket();
    // Чтение запроса
    void readRequest();
    // Обработка ошибок
    void displayError(QAbstractSocket::SocketError socketError);
    // Очистка соединения
    void clearSocket();

private:
    // Устройство
    QScopedPointer<DeviceEmulator> m_emulator;
    // Сервер
    QTcpServer *tcpServer;
    // Количество соединенных клиентов
    int clientsConnected;

    // Обработка команды
    QString processCommand(const QString &_command);
    // Отчет о статусе
    void reportStatus();
    // Адрес сервера
    QString serverAddress() const;
};

#endif // MANAGER_H
