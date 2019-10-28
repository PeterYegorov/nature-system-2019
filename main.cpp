#include "mainwindow.h"

#include <QApplication>


int Technical::width = 0;
int Technical::height = 0;

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    QApplication a(argc, argv);


    MainWindow w;

    w.show();




    return a.exec();
}
