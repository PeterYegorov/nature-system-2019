#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //-----------------------------------------Food Spawn---------------------------------------
    size_t regFoodsCount = rand() % 11 + 10;
    for (size_t i = 0; i < regFoodsCount; ++i)
    {
        foods.push_back(Food(rand() % width(),rand() % height()));
    }

    size_t PoiFoodsCount = rand() % 5;
    for (size_t i = 0; i < PoiFoodsCount; ++i)
    {
        poisonousFoods.push_back(PoisonousFood(rand() % width(),rand() % height()));

    }

    //----------------------------------------Herbivores spawn---------------------------------
    size_t herbsCount = rand() % 10 + 5;
    for (size_t i = 0; i < herbsCount; ++i)
    {
        herbs.push_back(Herbivores(rand() % width(),rand() % height()));
    }


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(doit()));
    timer->start(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::paintEvent(QPaintEvent *event){

    painter.begin(this);
//------------------------------------------
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, width(), height());

    painter.setBrush(Qt::yellow);

    for(size_t i = 0; i < foods.size(); ++i)
        painter.drawEllipse(foods[i].getX(), foods[i].getY(), 10, 10);

    painter.setBrush(Qt::cyan);
    for(size_t i = 0; i < poisonousFoods.size(); ++i)
        painter.drawEllipse(poisonousFoods[i].getX(), poisonousFoods[i].getY(), 10, 10);

    painter.setBrush(QColor(100,255,100));
    for(size_t i = 0; i < herbs.size(); ++i)
        painter.drawRect(herbs[i].x, herbs[i].y, 20, 20);

//------------------------------------------
    painter.end();


}

void MainWindow::doit()
{
    for(auto &i : herbs)
    {
        if(i.aim == nullptr)
            i.getAim(foods);
        i.move();

    }
    update();
}

