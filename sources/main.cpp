#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    QApplication a(argc, argv);

    MainWindow w;

    w.show();

    return a.exec();
}
