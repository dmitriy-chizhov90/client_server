#include <QtGui>

#include <stdlib.h>

#include "server.h"

Server::Server(QWidget *parent)
    : QDialog(parent)
    , statusLabel(new QLabel)
    , console(new QTextEdit)
    , quitButton (new QPushButton(tr("Quit")))
    , manager(new Manager(this))
{
    quitButton->setAutoDefault(false);

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(manager, SIGNAL(message(QString)), this, SLOT(message(QString)));
    connect(manager, SIGNAL(statusChanged(QString)), this, SLOT(statusChanged(QString)));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(console);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Server"));

    manager->launchServer();
}

void Server::message(const QString &_str)
{
    console->append(_str);
}

void Server::statusChanged(const QString &_status)
{
    statusLabel->setText(_status);
}
