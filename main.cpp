#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Home");
    QCoreApplication::setApplicationName("ScriptMakerApp");

    MainWindow w;
    w.show();
    return a.exec();
}
