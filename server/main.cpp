#include "server.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server w;
    w.show();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    return a.exec();
}
