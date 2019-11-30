#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <iostream>
#include <vector>
#include <ctime>
#include <utility>
#include <algorithm>
#include <any>
#include "initialparameters.h"

#include "predators.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

     QPainter painter;


    ~MainWindow();


private slots:
    void doit();



private:
    Ui::MainWindow *ui;
};




#endif // MAINWINDOW_H

