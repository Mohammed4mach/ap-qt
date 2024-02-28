#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QFile>

int main(int argc, char *argv[])
{
    QString home = QDir::homePath();
    QFile list_file = QFile(home + "/.apqt");

    if(!list_file.exists())
    {
        list_file.open(QIODevice::WriteOnly);
        list_file.close();
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
