#include <QtGui>
#include <QtNetwork>

#include "clientdialog.h"
#include "ui_clientdialog.h"

ClientDialog::ClientDialog(QWidget *parent)
:   QDialog(parent),
    ui(new Ui::ClientDialog)
  , manager(new Manager(this))
  , timer(-1)
{
    ui->setupUi(this);

    ui->hostLineEdit->setText(initialIp());
    ui->portLineEdit->setValidator(new QIntValidator(1, 65535, this));

    ui->connect->setEnabled(false);

    quitButton = new QPushButton(tr("Quit"));

    ui->buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->redButton);
    buttonGroup->addButton(ui->greenButton);
    buttonGroup->addButton(ui->blueButton);

    connect(ui->hostLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(enableInterface()));
    connect(ui->portLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(enableInterface()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(manager, SIGNAL(stateChanged()), this, SLOT(stateChanged()));
    connect(manager, SIGNAL(statusChanged()), this, SLOT(statusChanged()));
    connect(manager, SIGNAL(message(QString)), this, SLOT(appendLogMessage(QString)));
    connect(manager, SIGNAL(displayError(QAbstractSocket::SocketError,QString)),
            this, SLOT(displayError(QAbstractSocket::SocketError,QString)));

    ui->portLineEdit->setFocus();
    ui->connect->setEnabled(false);

    enableInterface();
}

ClientDialog::~ClientDialog()
{
    delete ui;
}

void ClientDialog::on_connect_clicked()
{
    if(manager->connected()) {
        manager->disconnectFromServer();
    } else {
        manager->connectToServer(ui->hostLineEdit->text(), ui->portLineEdit->text().toInt());
    }
}

void ClientDialog::on_update_clicked()
{
    manager->updateState();
}

void ClientDialog::on_submit_clicked()
{
    LedState state;
    state.on = ui->stateButton->isChecked();
    if(ui->redButton->isChecked()) {
        state.color = RedColor;
    } else if(ui->greenButton->isChecked()) {
        state.color = GreenColor;
    } else if(ui->blueButton->isChecked()) {
        state.color = BlueColor;
    }
    state.rate = ui->rateEdit->value();
    manager->submitState(state);
}

void ClientDialog::on_autoUpdate_stateChanged(int)
{
    static const int msecs = 3000;
    enableInterface();
    if(ui->autoUpdate->isChecked()) {
        timer = startTimer(msecs);
    } else {
        killTimer(timer);
    }
}

void ClientDialog::displayError(QAbstractSocket::SocketError socketError, const QString &error)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(error));
    }
    ui->connect->setEnabled(true);
}

void ClientDialog::enableInterface()
{
    ui->stateWidget->setEnabled(manager->connected());

    ui->update->setEnabled(!ui->autoUpdate->isChecked() && manager->connected());
    ui->submit->setEnabled(!ui->autoUpdate->isChecked() && manager->connected());
    ui->connect->setEnabled(manager->connected() || (!ui->hostLineEdit->text().isEmpty() &&
                                 !ui->portLineEdit->text().isEmpty()));
    ui->connect->setText(manager->connected() ? tr("Disconnect") : tr("Connect"));
}

void ClientDialog::timerEvent(QTimerEvent *)
{
    if(manager->connected() && ui->autoUpdate->isChecked()) {
        on_update_clicked();
    }
}

QString ClientDialog::initialIp() const
{
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    return ipAddress;
}

void ClientDialog::stateChanged()
{
    LedState state = manager->state();
    ui->stateButton->setChecked(state.on);
    switch(state.color) {
    case RedColor: {
        ui->redButton->setChecked(true);
        break;
    }
    case GreenColor: {
        ui->greenButton->setChecked(true);
        break;
    }
    case BlueColor: {
        ui->blueButton->setChecked(true);
        break;
    }
    default: {
        break;
    }
    }
    ui->rateEdit->setValue(state.rate);
}

void ClientDialog::statusChanged()
{
    ui->statusLabel->setText(manager->status());
    enableInterface();
}

void ClientDialog::appendLogMessage(const QString &msg)
{
    ui->console->append(msg);
}


