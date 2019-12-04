#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "initialparameters.h"
#include "environment.h"
#include "omnivorous.h"
#include "mainmenu.h"
#include <QtDebug>

std::vector<Food> Environment::foods;
std::vector<Herbivores> Environment::herbs;
std::vector<Predators> Environment::preds;
std::vector<Omnivorous> Environment::oms;
bool Technical::allHerbsDied;
size_t Technical::ID;
int Technical::time;

QTimer *MainMenu::timer = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Technical::time = 0;
    Technical::width = width();
    Technical::height = height();
    Technical::ID = 0;



    MainMenu::timer = new QTimer(this);
    connect(MainMenu::timer, SIGNAL(timeout()), this, SLOT(doit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::paintEvent(QPaintEvent *event) {

    QImage image(Technical::width, Technical::height, QImage::Format_RGB32);
    painter.begin(&image);
    //------------------------------------------
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, width(), height());

    painter.setBrush(Qt::yellow);

    for(size_t i = 0; i < Environment::foods.size(); ++i)
        painter.drawEllipse(Environment::foods[i].getX(), Environment::foods[i].getY(), 10, 10);

    for(size_t i = 0; i < Environment::herbs.size(); ++i) {
        painter.setBrush(QColor(100,255,100));
        painter.drawRect(Environment::herbs[i].x, Environment::herbs[i].y, Environment::herbs[i].height, Environment::herbs[i].width);
        if(Environment::herbs[i].sex){
            painter.setBrush(QColor(200,255,100));
            painter.drawRect(Environment::herbs[i].x + 2, Environment::herbs[i].y + 2, Environment::herbs[i].height/3, Environment::herbs[i].width/3);
        }
    }



    for(size_t i = 0; i < Environment::preds.size(); ++i) {
        painter.setBrush(QColor(255,50,0));
        painter.drawRect(Environment::preds[i].x, Environment::preds[i].y, Environment::preds[i].height, Environment::preds[i].width);
        if(Environment::preds[i].sex) {
            painter.setBrush(QColor(250,195,0));
            painter.drawRect(Environment::preds[i].x + 2, Environment::preds[i].y + 2, Environment::preds[i].height/3, Environment::preds[i].width/3);
        }
    }


    for(size_t i = 0; i < Environment::oms.size(); ++i) {
        painter.setBrush(QColor(10,200,200));
        painter.drawRect(Environment::oms[i].x, Environment::oms[i].y, Environment::oms[i].height, Environment::oms[i].width);
        if(Environment::oms[i].sex) {
            painter.setBrush(QColor(10,100,200));
            painter.drawRect(Environment::oms[i].x + 2, Environment::oms[i].y + 2, Environment::oms[i].height/3, Environment::oms[i].width/3);
        }
    }

    painter.setPen(Qt::white);
    painter.setFont(QFont("times", 22));
    painter.drawText(10, 30, "Травоядные: " + QString::number(Environment::herbs.size()));
    painter.drawText(10, 90, "Хищники: " + QString::number(Environment::preds.size()));
    painter.drawText(10, 150, "Всеядные: " + QString::number(Environment::oms.size()));
    painter.drawText(10, 210, "Время: " + QString::number(Technical::time/20));
    painter.setFont(QFont("times", 10));
    for (size_t i = 0; i < Environment::preds.size(); ++i) {
      //  if(Environment::preds[i].repAim != nullptr)
        painter.drawText(10, (270 + i*20), "herb " + QString::number(i) + ":" + QString::number(Environment::preds[i].satiety));
    }
    //------------------------------------------
    painter.end();


    //------------------------------------------
    painter.begin(this);
    painter.drawImage(0,0, image);
    painter.end();
    //------------------------------------------


  //  ui->SimulationLabel->setStyleSheet("QLabel { color : black; }");
    ui->SimulationLabel->hide();

    if(Environment::herbs.size() == 0){

        MainMenu::timer->stop();
        ui->SimulationLabel->show();
        ui->SimulationLabel->setStyleSheet("QLabel { color : white; }");

        ui->SimulationLabel->setText("Overall time: "+ QString::number(Technical::time/20));

    }



}

void MainWindow::doit()
{
    ++Technical::time;
    if(Environment::herbs.size() == 0)
        Technical::allHerbsDied = true;

    for (std::vector<Herbivores>::iterator it=Environment::herbs.begin(); it!=Environment::herbs.end(); )
    {
        it->repAim = nullptr;
        it->satiety -= 0.01;
        --it->age;
        if (it->repAim == nullptr)
        {
            it->getAim(Environment::foods);
            it->eat();
            if (it->satiety > InitialParameters::herbsRepSatiety && it->young <= 0 && Environment::checkRepPossibility(*it, Environment::herbs)){
                it->foodAim = nullptr;
                it->getRepAim(Environment::herbs);
            }
        }
        if (it->repAim != nullptr && Technical::Destination(it->x, it->y, it->repAim->x, it->repAim->y) < 30) {

            it->reproduce();

            if(it->sex == true)
                Environment::herbs.push_back(it->birth(it->x, it->y));

            return;
        }

        for (size_t i = 0; i < Environment::preds.size(); ++i) {
            if(Technical::Destination(it->x, it->y, Environment::preds[i].x, Environment::preds[i].y) < 100) {
                it->danger = 30;
                break;
            }
        }

        for (size_t i = 0; i < Environment::oms.size(); ++i) {
            if(Technical::Destination(it->x, it->y, Environment::oms[i].x, Environment::oms[i].y) < 100) {
                it->danger = 30;
                break;
            }
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

int aaa = 0;
    for (std::vector<Predators>::iterator it=Environment::preds.begin(); it!=Environment::preds.end(); )
    {
        aaa++;
        it->repAim = nullptr;
        it->satiety -= 0.01;
        --it->age;
       // it->repAim = nullptr;
      /*if (Environment::herbs.size() == 0) {
            it->foodAim = nullptr;
            it->getRepAim(Environment::preds);
      }*/
        if (it->repAim == nullptr)
        {
            if (Environment::herbs.size() > 0) {
                it->foodAim = nullptr;
                it->getFoodAim(Environment::herbs);
                it->eat();
            }
            if (it->satiety > InitialParameters::predsRepSatiety && it->young <= 0 && Environment::checkRepPossibility(*it, Environment::preds)) {
                it->foodAim = nullptr;
                it->getRepAim(Environment::preds);



                qDebug() << "Pred " << it->ID << ": " << it->satiety << " " << InitialParameters::predsRepSatiety;

            }
        }
        if (it->repAim != nullptr && Technical::Destination(it->x, it->y, it->repAim->x, it->repAim->y) < 30) {

            it->reproduce();

            if(it->sex == true)
                Environment::preds.push_back(it->birth(it->x, it->y));

            return;
        }

        for (size_t i = 0; i < Environment::oms.size(); ++i) {
            if(Technical::Destination(it->x, it->y, Environment::oms[i].x, Environment::oms[i].y) < 100) {
                it->danger = 30;
                break;
            }
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

    for (std::vector<Omnivorous>::iterator it=Environment::oms.begin(); it!=Environment::oms.end(); )
    {
        it->satiety -= 0.01;
        --it->age;
        it->repAim = nullptr;

        if (it->repAim == nullptr)
        {
                //it->getFoodAim(Environment::toObject(Environment::herbs), Environment::toObject(Environment::foods));
                if(Environment::herbs.size()>0)
                    it->foodAim = it->getFoodAim(Environment::herbs);
                it->foodAim = it->getFoodAim(Environment::foods);
                if(Environment::preds.size()>0)
                    it->foodAim = it->getFoodAim(Environment::preds);
                it->omsEat(Environment::foods, Environment::herbs, Environment::preds);
            if (it->satiety > InitialParameters::omsRepSatiety && it->young <= 0  && Environment::checkRepPossibility(*it, Environment::oms)) {
                it->foodAim = nullptr;
                it->getRepAim(Environment::oms);
            }
        }
        if (it->repAim != nullptr && Technical::Destination(it->x, it->y, it->repAim->x, it->repAim->y) < 30) {

            it->reproduce();

            if(it->sex == true)
                Environment::oms.push_back(it->birth(it->x, it->y));
            return;
        }

        it->move();
        it->die();
            if (it->isDead)
            {
                Environment::oms.erase(it);
                break;
            }
            else
                ++it;
     }

    update();
}

