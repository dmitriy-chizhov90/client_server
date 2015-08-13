#ifndef SERVER_H
#define SERVER_H

#include "manager.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

// ���� �������
class Server : public QDialog
{
    Q_OBJECT

public:
    Server(QWidget *parent = 0);

private slots:
    // ���������� ���������
    void message(const QString &_str);
    // ���������� ������
    void statusChanged(const QString &_status);

private:
    // ���������
    QLabel *statusLabel;
    QTextEdit *console;
    QPushButton *quitButton;
    // ��������
    Manager *manager;
};

#endif // SERVER_H
