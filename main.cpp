#include "mainwindow.h"

#include <QApplication>
#include <utils/librarymanager.h>

int main(int argc, char *argv[])
{
    LibraryManager::create_storage();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
