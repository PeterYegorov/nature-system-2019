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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



//-------------------------Technical classes-------------
class Technical {
public:

    static int width;
    static int height;
    static const int normalSatiety = 100;
    static double Destination(const int& x1, const int& y1, const int& x2, const int& y2){
        return sqrt(pow(x2 - x1,2) + pow(y2 - y1,2));
    }
};


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

    static void regenerateFood(Food *fAim) {
        fAim->x = rand() % Technical::width;
        fAim->y = rand() % Technical::height;
    }
};


class differentFood : public Food
{
public:
    differentFood(int x, int y) : Food(x,y) {}
};



//---------------------Animal classes--------------------

class Animal
{
public:
    int x, y;
    int hp;
    double satiety;
    int speed;
    int age;
    int young;
    int width, height;
    bool isDead;

    Animal *repAim;

    virtual void move() = 0;
    virtual void eat() = 0;
    virtual void reproduct() = 0;
    virtual void die() = 0;
};

//-------------------------------------------------------

class Herbivores : public Animal
{

public:
    Food *foodAim;
    Herbivores(int x, int y, int isyoung = 100) {
        this->x = x;
        this->y = y;
        hp =  100;
        satiety = 10;
        speed = 7;
        age = rand() % 100 + 10000000;
        foodAim = nullptr;
        repAim = nullptr;
        isDead = false;
        this->young = isyoung;

        if(this->young > 0)
        {
            width = 10;
            height = 10;
        }
        else {
            width = 20;
            height = 20;
        }
    }
    void move() override
    {
        if (young <= 0){
            height = 20;
            width = 20;
            speed = 7;
        } else
            --young;
        if (foodAim != nullptr)
        {
        if(this->x > foodAim->x)
            this->x -= speed;
        if(this->x < foodAim->x)
            this->x += speed;
        if(this->y > foodAim->y)
            this->y -= speed;
        if(this->y < foodAim->y)
            this->y += speed;
        }

        if (repAim != nullptr)
        {
            if(this->x > repAim->x)
                this->x -= speed;
            if(this->x < repAim->x)
                this->x += speed;
            if(this->y > repAim->y)
                this->y -= speed;
            if(this->y < repAim->y)
                this->y += speed;
        }
    }

    void getAim(std::vector<Food>& vec)
    {
        //repAim = nullptr;
        double min = Technical::Destination(x,y,vec[0].x, vec[0].y);
        foodAim = &vec[0];
        //for(Food i : vec) Почему-то не работает
        for(size_t i = 1; i < vec.size(); ++i)
        {
            if (Technical::Destination(x,y,vec[i].x, vec[i].y) < min)
            {
                min = Technical::Destination(x,y,vec[i].x, vec[i].y);
                foodAim = &vec[i];
            }
        }
    }

    void getRepAim(std::vector<Herbivores>& vec)
    {

        double min = 10000000;

        for(size_t i = 0; i < vec.size(); ++i)
        {
            if (this != &vec[i] && Technical::Destination(x,y,vec[i].x, vec[i].y) < min)
            {
                min = Technical::Destination(x,y,vec[i].x, vec[i].y);
                repAim = &vec[i];
            }
        }
    }

    void eat() override
    {
        if(Technical::Destination(x, y, foodAim->x, foodAim->y) < 30)
        {
            if (young > 0){
                satiety += 10;
            } else
                satiety += 50;
            Food::regenerateFood(foodAim);
            foodAim = nullptr;
        }
    }

    void reproduct() override
    {
            satiety -= 50;
            repAim->satiety -= 50;
            static_cast<Herbivores*>(repAim)->repAim = nullptr;
            repAim = nullptr;
    }

    void die() override {
         if (satiety <= 0 || age <= 0){
             isDead = true;
         }
    }


    Herbivores birth(int birthX, int birthY) {
        Herbivores baby(birthX, birthY);
        baby.hp = 50;
        baby.satiety = 50;
        baby.speed = 10;
        return baby;
    }

    virtual ~Herbivores() {}
};
//---------------------------------------------------------

class Predators : public Animal {

public:
    Herbivores *foodAim;
    Predators(int x, int y, int isyoung = 100) {
        this->x = x;
        this->y = y;
        hp =  100;
        satiety = 10;
        speed = 7;
        age = rand() % 100 + 1000000;
        foodAim = nullptr;
        repAim = nullptr;
        isDead = false;
        this->young = isyoung;

        if(this->young > 0)
        {
            width = 10;
            height = 10;
        }
        else {
            width = 20;
            height = 20;
        }
    }

    void move() override {

        if (young <= 0){
            height = 20;
            width = 20;
            speed = 7;
        } else
            --young;
        if (foodAim != nullptr)
        {
        if(this->x > foodAim->x)
            this->x -= speed;
        if(this->x < foodAim->x)
            this->x += speed;
        if(this->y > foodAim->y)
            this->y -= speed;
        if(this->y < foodAim->y)
            this->y += speed;
        }

        if (repAim != nullptr)
        {
            if(this->x > repAim->x)
                this->x -= speed;
            if(this->x < repAim->x)
                this->x += speed;
            if(this->y > repAim->y)
                this->y -= speed;
            if(this->y < repAim->y)
                this->y += speed;
        }

        if(foodAim == nullptr && repAim == nullptr){
            int randDestination = rand() % 4;
            if(randDestination == 1)
                this->x -= speed;
            if(randDestination == 2)
                this->x += speed;
            if(randDestination == 3)
                this->y -= speed;
            if(randDestination == 4)
                this->y += speed;
        }
    }

    void getFoodAim(std::vector<Herbivores>& vec) {

        double min = Technical::Destination(x,y,vec[0].x, vec[0].y);
        foodAim = &vec[0];

        for(size_t i = 1; i < vec.size(); ++i)
        {
            if (Technical::Destination(x,y,vec[i].x, vec[i].y) < min)
            {
                min = Technical::Destination(x,y,vec[i].x, vec[i].y);
                foodAim = &vec[i];
            }
        }
    }

    void eat() override {
        if(Technical::Destination(x, y, foodAim->x, foodAim->y) < 30)
        {
            if (young > 0){
                satiety += 10;
            } else
                satiety += 50;
            foodAim->isDead = true;
            foodAim = nullptr;
        }
    }

    void die() override {
         if (satiety <= 0 || age <= 0){
             isDead = true;
         }
    }

    void getRepAim(std::vector<Predators> vec) {
        double min = 100000000;

        for(size_t i = 0; i < vec.size(); ++i)
        {
            if (this != &vec[i] && Technical::Destination(x,y,vec[i].x, vec[i].y) < min)
            {
                min = Technical::Destination(x,y,vec[i].x, vec[i].y);
                repAim = &vec[i];
            }
        }

    }

    void reproduct() override {
        satiety -= 50;
        repAim->satiety -= 50;
        static_cast<Predators*>(repAim)->repAim = nullptr;
        repAim = nullptr;
    }

    Predators birth(int birthX, int birthY) {
        Predators baby(birthX, birthY);
        baby.hp = 50;
        baby.satiety = 50;
        baby.speed = 10;
        return baby;
    }


    virtual ~Predators() {}
};


//---------------------Environment classes-----------------


class Environment {
public:
    static std::vector<Food> foods;
    static std::vector<differentFood> differentFoods;
    static std::vector<Herbivores> herbs;
    static std::vector<Predators> preds;
};
//-------------------------------------------------------

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

