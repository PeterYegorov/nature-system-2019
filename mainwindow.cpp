#include "mainwindow.h"
#include "ui_mainwindow.h"


std::vector<Food> Environment::foods;
std::vector<differentFood> Environment::differentFoods;
std::vector<Herbivores> Environment::herbs;
std::vector<Predators> Environment::preds;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Technical::width = width();
    Technical::height = height();

    //-----------------------------------------Food Spawn---------------------------------------
    size_t regFoodsCount = rand() % 11 + 10;
    // size_t regFoodsCount = 1;
    // size_t regFoodsCount = 100;
    for (size_t i = 0; i < regFoodsCount; ++i)
    {
        Environment::foods.push_back(Food(rand() % width(),rand() % height()));
    }

    size_t PoiFoodsCount = rand() % 5;
    for (size_t i = 0; i < PoiFoodsCount; ++i)
    {
        Environment::differentFoods.push_back(differentFood(rand() % width(),rand() % height()));

    }

    //----------------------------------------Herbivores spawn---------------------------------
    //size_t herbsCount = rand() % 10 + 5;
    size_t herbsCount = 20;
    for (size_t i = 0; i < herbsCount; ++i)
    {
        Environment::herbs.push_back(Herbivores(rand() % width(),rand() % height(), false));
    }
    //----------------------------------------Predators spawn---------------------------------
    size_t predsCount = 10;
    for (size_t i = 0; i < predsCount; ++i)
    {
        Environment::preds.push_back(Predators(rand() % width(),rand() % height(), false));
    }

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(doit()));
    timer->start(50);

}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::paintEvent(QPaintEvent *event) {

    painter.begin(this);
//------------------------------------------
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, width(), height());

    painter.setBrush(Qt::yellow);

    for(size_t i = 0; i < Environment::foods.size(); ++i)
        painter.drawEllipse(Environment::foods[i].getX(), Environment::foods[i].getY(), 10, 10);

    painter.setBrush(Qt::cyan);
    for(size_t i = 0; i < Environment::differentFoods.size(); ++i)
        painter.drawEllipse(Environment::differentFoods[i].getX(), Environment::differentFoods[i].getY(), 10, 10);

    painter.setBrush(QColor(100,255,100));
    for(size_t i = 0; i < Environment::herbs.size(); ++i)
        painter.drawRect(Environment::herbs[i].x, Environment::herbs[i].y, Environment::herbs[i].height, Environment::herbs[i].width);


    painter.setBrush(QColor(255,50,0));
    for(size_t i = 0; i < Environment::preds.size(); ++i)
        painter.drawRect(Environment::preds[i].x, Environment::preds[i].y, Environment::preds[i].height, Environment::preds[i].width);

//------------------------------------------
    painter.end();


}

void MainWindow::doit()
{
    for (std::vector<Herbivores>::iterator it=Environment::herbs.begin(); it!=Environment::herbs.end(); )
    {
        it->satiety -= 0.01;
        --it->age;
        if (it->repAim == nullptr)
        {
            it->getAim(Environment::foods);
            it->eat();
            if (it->satiety > 100 && it->young <= 0){
                it->foodAim = nullptr;
                it->getRepAim(Environment::herbs);
            }
        }
        else if (it->foodAim == nullptr && Technical::Destination(it->x, it->y, it->repAim->x, it->repAim->y) < 30) {

            it->reproduct();

            Environment::herbs.push_back(it->birth(it->x, it->y));
            return;
        }

        it->move();
        it->die();
            if (it->isDead)
            {
                Environment::herbs.erase(it);
                break;
            }
            else
                ++it;
     }


    for (std::vector<Predators>::iterator it=Environment::preds.begin(); it!=Environment::preds.end(); )
    {
        it->satiety -= 0.01;
        --it->age;
      /*if (Environment::herbs.size() == 0) {
            it->foodAim = nullptr;
      }*/
        if (it->repAim == nullptr && Environment::herbs.size() > 0)
        {
            it->getFoodAim(Environment::herbs);
            it->eat();
            if (it->satiety > 100 && it->young <= 0) {
                //it->foodAim = nullptr;
                it->getRepAim(Environment::preds);
            }
        }
        else if (it->foodAim == nullptr && Technical::Destination(it->x, it->y, it->repAim->x, it->repAim->y) < 30) {

            it->reproduct();

            Environment::preds.push_back(it->birth(it->x, it->y));
            return;
        }

        it->move();
        it->die();
            if (it->isDead)
            {
                Environment::preds.erase(it);
                break;
            }
            else
                ++it;
     }

    update();
}

