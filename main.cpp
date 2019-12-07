#include "mainwindow.h"
#include "mainmenu.h"
#include <QApplication>

int Technical::width = 0;
int Technical::height = 0;

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    MainMenu menu;
    menu.show();
    return a.exec();
}
