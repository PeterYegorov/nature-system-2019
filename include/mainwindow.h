#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <iostream>
#include <vector>
#include <ctime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


//---------------------Food classes----------------------

class Food
{
public:
    int x, y;

    Food() {}
    Food(int x, int y) {
        this->x = x;
        this->y = y;
    }
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
};


class PoisonousFood : public Food
{
public:
    PoisonousFood(int x, int y) : Food(x,y) {}
};

//---------------------Technical classes-----------------

class Technical {
    public:

    static double Destination(const int& x1, const int& y1, const int& x2, const int& y2){
        return sqrt(pow(x2 - x1,2) + pow(y2 - y1,2));
    }
};

//---------------------Animal classes--------------------

class Animal
{
public:
    int x, y;
    int hp;
    int satiety;
    int speed;

    virtual void move() = 0;

};

class Herbivores : public Animal
{

public:
    Food *aim;
    Herbivores(int x, int y) {
        this->x = x;
        this->y = y;
        hp =  100;
        satiety = 100;
        speed = 7;
        aim = nullptr;
    }
    void move() override
    {
        if(this->x > aim->x)
            this->x -= speed;
        if(this->x < aim->x)
            this->x += speed;
        if(this->y > aim->y)
            this->y -= speed;
        if(this->y < aim->y)
            this->y += speed;
    }

    void getAim(std::vector<Food>& vec)
    {
        double min = Technical::Destination(x,y,vec[0].x, vec[0].y);
        aim = &vec[0];
        //for(Food i : vec) Почему-то не работает
        for(size_t i = 0; i < vec.size(); ++i)
        {
            if (Technical::Destination(x,y,vec[i].x, vec[i].y) < min)
            {
                min = Technical::Destination(x,y,vec[i].x, vec[i].y);
                aim = &vec[i];
            }
        }
    }

    virtual ~Herbivores() {}
};

//-------------------------------------------------------

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

     QPainter painter;



     std::vector<Food> foods;
     std::vector<PoisonousFood> poisonousFoods;
     std::vector<Herbivores> herbs;



    ~MainWindow();


private slots:
    void doit();



private:
    Ui::MainWindow *ui;
};




#endif // MAINWINDOW_H

