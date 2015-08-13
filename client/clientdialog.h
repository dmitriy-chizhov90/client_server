#ifndef CLIENTDIALOG_H
#define CLIENTDIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include "manager.h"

namespace Ui {
class ClientDialog;
}

// ��������� �������
class ClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientDialog(QWidget *parent = 0);
    ~ClientDialog();

private slots:
    // ������ ���������/�����������
    void on_connect_clicked();
    // ������ ��������
    void on_update_clicked();
    // ������ ���������
    void on_submit_clicked();
    // ���� ��������������� ����������
    void on_autoUpdate_stateChanged(int);
    // ���������� ������
    void displayError(QAbstractSocket::SocketError socketError, const QString &error);
    // ��������� ��������� ����������
    void stateChanged();
    // ��������� �������
    void statusChanged();
    // �������� ���������
    void appendLogMessage(const QString &msg);
    // ��������� ����������� ��������� ����������
    void enableInterface();

protected:
    void timerEvent(QTimerEvent *);

private:
    Ui::ClientDialog *ui;
    // ���������
    QPushButton *quitButton;
    QButtonGroup *buttonGroup;
    // ��������
    Manager *manager;
    // ������
    int timer;

    // ��������� ip-�����
    QString initialIp() const;
};

#endif // CLIENTDIALOG_H
