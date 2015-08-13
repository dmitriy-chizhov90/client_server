#ifndef MANAGER_H
#define MANAGER_H

#include <QStringList>
#include <QTcpSocket>
#include <QObject>

#include "ledstate.h"
#include "protocol.h"

// Класс отсылает и получает сообщения по сети
class Manager : public QObject
{
    Q_OBJECT
public:
    Manager(QObject *_parent = 0);
    // Состояние устройства
    LedState state() const { return m_state; }
    // Обновить состояние
    void updateState();
    // Отправить состояние
    void submitState(const LedState &_state);
    // Статус менеджера
    QString status() const { return m_status; }
    // Проверка соединения
    bool connected() const;

public Q_SLOTS:
    // Соединиться с сервером
    void connectToServer(const QString &_host, int _port);
    // Разорвать соединение
    void disconnectFromServer();

Q_SIGNALS:
    // Состояние устройства изменилось
    void stateChanged();
    // Статус изменился
    void statusChanged();
    // Сообщение
    void message(const QString &_msg);
    // Сообщение об ошибке
    void displayError(QAbstractSocket::SocketError, const QString &);

private Q_SLOTS:
    // Чтение сообщения по сети
    void readFromSocket();
    // Обработка ошибок
    void displayError(QAbstractSocket::SocketError _socketError);
    // Обработка разрыва соединения
    void disconnected();

private:
    QTcpSocket *m_tcpSocket;
    // Статус
    QString m_status;
    // Состояние устройства
    LedState m_state;
    // Текущая команда
    ECommand m_currentCommand;
    // Очередь команд
    QList<ECommand> m_commands;

    // Установить статус
    void setStatus(const QString &_status);
    // Выполнить команду из очереди
    void executeCommands();
};

#endif // MANAGER_H
