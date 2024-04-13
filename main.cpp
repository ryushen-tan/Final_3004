#include "mainwindow.h"
//#include <QFile>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    //TODO: create battery and log files to read and write for persisting information
//    Qstring filename = "battery.txt";
}
