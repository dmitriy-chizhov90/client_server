#ifndef SERVER_H
#define SERVER_H

#include "manager.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

// Окно сервера
class Server : public QDialog
{
    Q_OBJECT

public:
    Server(QWidget *parent = 0);

private slots:
    // Отобразить сообщение
    void message(const QString &_str);
    // Отобразить статус
    void statusChanged(const QString &_status);

private:
    // Интерфейс
    QLabel *statusLabel;
    QTextEdit *console;
    QPushButton *quitButton;
    // Менеджер
    Manager *manager;
};

#endif // SERVER_H
