/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *portLabel;
    QLabel *hostLabel;
    QLineEdit *hostLineEdit;
    QLineEdit *portLineEdit;

    void setupUi(QDialog *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(493, 361);
        verticalLayoutWidget = new QWidget(Client);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(30, 10, 281, 161));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget = new QWidget(Client);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(140, 260, 160, 80));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        portLabel = new QLabel(gridLayoutWidget);
        portLabel->setObjectName(QString::fromUtf8("portLabel"));

        gridLayout->addWidget(portLabel, 1, 0, 1, 1);

        hostLabel = new QLabel(gridLayoutWidget);
        hostLabel->setObjectName(QString::fromUtf8("hostLabel"));

        gridLayout->addWidget(hostLabel, 0, 0, 1, 1);

        hostLineEdit = new QLineEdit(gridLayoutWidget);
        hostLineEdit->setObjectName(QString::fromUtf8("hostLineEdit"));

        gridLayout->addWidget(hostLineEdit, 0, 1, 1, 1);

        portLineEdit = new QLineEdit(gridLayoutWidget);
        portLineEdit->setObjectName(QString::fromUtf8("portLineEdit"));

        gridLayout->addWidget(portLineEdit, 1, 1, 1, 1);

#ifndef QT_NO_SHORTCUT
        portLabel->setBuddy(portLineEdit);
        hostLabel->setBuddy(hostLineEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QDialog *Client)
    {
        Client->setWindowTitle(QApplication::translate("Client", "Dialog", 0, QApplication::UnicodeUTF8));
        portLabel->setText(QApplication::translate("Client", "S&erver port:", 0, QApplication::UnicodeUTF8));
        hostLabel->setText(QApplication::translate("Client", "&Server name:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
