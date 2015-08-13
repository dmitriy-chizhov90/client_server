#ifndef CLIENTDIALOG_H
#define CLIENTDIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include "manager.h"

namespace Ui {
class ClientDialog;
}

// Интерфейс клиента
class ClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientDialog(QWidget *parent = 0);
    ~ClientDialog();

private slots:
    // Кнопка соединить/разъединить
    void on_connect_clicked();
    // Кнопка обновить
    void on_update_clicked();
    // Кнопка отправить
    void on_submit_clicked();
    // Флаг автоматического обновления
    void on_autoUpdate_stateChanged(int);
    // Отобразить ошибку
    void displayError(QAbstractSocket::SocketError socketError, const QString &error);
    // Изменение состояния устройства
    void stateChanged();
    // Изменения статуса
    void statusChanged();
    // Добавить сообщение
    void appendLogMessage(const QString &msg);
    // Изменение доступности элементов интерфейса
    void enableInterface();

protected:
    void timerEvent(QTimerEvent *);

private:
    Ui::ClientDialog *ui;
    // Интерфейс
    QPushButton *quitButton;
    QButtonGroup *buttonGroup;
    // Менеджер
    Manager *manager;
    // Таймер
    int timer;

    // Начальный ip-адрес
    QString initialIp() const;
};

#endif // CLIENTDIALOG_H
