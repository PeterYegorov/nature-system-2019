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
    static bool allHerbsDied;
    static bool allPredsDIed;
    static size_t ID;
    static int time;
};

class Object {
public:
    int x, y;
    bool isDead;
    size_t ID;
};

//---------------------Food classes----------------------

class Food : public Object
{
public:
    Food() {}
    Food(int x, int y) {
        this->x = x;
        this->y = y;
        ID = ++Technical::ID;
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

class Animal : public Object
{
public:
    int hp;
    double satiety;
    int speed;
    int age;
    int young;
    int width, height;
    bool sex;
    int danger;


   // Animal *repAim;

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
    std::shared_ptr<Herbivores >repAim;
    Herbivores(int x, int y, int isyoung = 100) {
        this->x = x;
        this->y = y;
        hp =  100;
        satiety = 10;
        speed = 7;
        age = rand() % 100 + 1000;
        foodAim = nullptr;
        repAim = nullptr;
        isDead = false;
        this->young = isyoung;
        sex = rand()% 2;
        danger = 0;

        if(this->young > 0)
        {
            width = 10;
            height = 10;
        }
        else {
            width = 20;
            height = 20;
        }
        ID = ++Technical::ID;
    }

    void move() override
    {
        if (young <= 0){
            height = 20;
            width = 20;
            speed = 7;
        } else
            --young;

        if(danger > 0) {
            speed = 10;
            --danger;
        } else
            speed = 7;

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

       /* if(x < -50 || y < -50) {
            repAim->repAim = nullptr;
            repAim = nullptr;
        }*/
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
            if (this != &vec[i] && Technical::Destination(x,y,vec[i].x, vec[i].y) < min && sex != vec[i].sex)
            {
                min = Technical::Destination(x,y,vec[i].x, vec[i].y);
              //  repAim = &vec[0];
                repAim = std::make_shared<Herbivores>(vec[i]);
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
            satiety -= 500;
            repAim->satiety -= 500;

            //repAim->repAim.reset();
            repAim->repAim = nullptr;
            //repAim.reset();
            repAim = nullptr;
    }

    void die() override {
         if (satiety <= 0 || age <= 0 || hp <= 0){
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
    std::shared_ptr<Predators> repAim;
    bool foodMove = false;
    bool repMove = false;
    bool randMove = false;

    Predators(int x, int y, int isyoung = 100) {
        this->x = x;
        this->y = y;
        hp =  100;
        satiety = 10;
        speed = 7;
        danger = 0;
        age = rand() % 100 + 1000;
        foodAim = nullptr;
        repAim = nullptr;
        isDead = false;
        this->young = isyoung;
        sex = rand()% 2;

        if(this->young > 0)
        {
            width = 10;
            height = 10;
        }
        else {
            width = 20;
            height = 20;
        }
        ID = ++Technical::ID;
    }

    void move() override {


        if (young <= 0){
            height = 20;
            width = 20;
            speed = 7;
        } else
            --young;

        if(danger > 0) {
            speed = 10;
            --danger;
        } else
            speed = 7;

        if (foodAim != nullptr)
        {
            foodMove = true;
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
            repMove = true;
            if(this->x > repAim->x)
                this->x -= speed;
            if(this->x < repAim->x)
                this->x += speed;
            if(this->y > repAim->y)
                this->y -= speed;
            if(this->y < repAim->y)
                this->y += speed;
        }

        if(Technical::allHerbsDied){
            randMove = true;
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
        if(x < -50 || y < -50) {
            repAim->repAim = nullptr;
            repAim = nullptr;
        }
    }

    void getFoodAim(std::vector<Herbivores>& vec) {
        if(Technical::allHerbsDied)
            return;
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

            if(foodAim->hp > 0)
                foodAim->hp -= 10;

            if(foodAim->hp <= 0)
            {
                if (young > 0){
                    satiety += 10;
                } else
                    satiety += 50;
            }

            foodAim->isDead = true;
         //   foodMove = false;
            foodAim = nullptr;
        }
    }

    void die() override {
         if (satiety <= 0 || age <= 0 || hp <= 0){
             isDead = true;
         }
    }

    void getRepAim(std::vector<Predators>& vec) {
        double min = 100000000;

        for(size_t i = 0; i < vec.size(); ++i)
        {
            if (this != &vec[i] && Technical::Destination(x,y,vec[i].x, vec[i].y) < min && sex != vec[i].sex)
            {
                min = Technical::Destination(x,y,vec[i].x, vec[i].y);
                repAim = std::make_shared<Predators>(vec[i]);
            }
        }

    }

    void reproduct() override {
        satiety -= 50;
        repAim->satiety -= 50;
        repAim->repAim = nullptr;
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


class Omnivorous : public Animal {
public:
    Object *foodAim;
    std::shared_ptr<Omnivorous> repAim;
    Omnivorous(int x, int y, int isyoung = 100) {
        this->x = x;
        this->y = y;
        hp =  100;
        satiety = 10;
        speed = 7;
        age = rand() % 100 + 1000;
        foodAim = nullptr;
        repAim = nullptr;
        isDead = false;
        this->young = isyoung;
        sex = rand()% 2;

        if(this->young > 0)
        {
            width = 10;
            height = 10;
        }
        else {
            width = 20;
            height = 20;
        }
        ID = ++Technical::ID;
    }


    void move() override {

        if (young <= 0) {
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

    void eat() override {}

    void omsEat(std::vector<Food>& foodV, std::vector<Herbivores>& foodH, std::vector<Predators>& foodP) {
        if(Technical::Destination(x, y, foodAim->x, foodAim->y) < 30)
        {
            if (young > 0){
                satiety += 10;
            } else
                satiety += 50;

            for (std::vector<Food>::iterator iter = foodV.begin(); iter < foodV.end(); ++iter)
            {
                if(foodAim->ID == (*iter).ID)
                   {
                    (*iter).isDead = true;
                    foodAim = nullptr;

                    Food::regenerateFood(&(*iter));
                    return;
                 }
            }
            for (std::vector<Herbivores>::iterator iter = foodH.begin(); iter < foodH.end(); ++iter)
            {
                if(foodAim->ID == (*iter).ID) {
                    (*iter).hp -= 10;
                    foodAim = nullptr;
                   // foodH.erase(iter);
                    return;
                }
            }
            for (std::vector<Predators>::iterator iter = foodP.begin(); iter < foodP.end(); ++iter)
            {
                if(foodAim->ID == (*iter).ID) {
                    (*iter).hp -= 10;
                    foodAim = nullptr;
                  //  foodP.erase(iter);
                    return;
                    }
            }
           // foodAim->isDead = true;
            foodAim = nullptr;
        }
    }


    void die() override {
         if (satiety <= 0 || age <= 0 || hp <= 0){
             isDead = true;
         }
    }


    void getRepAim(std::vector<Omnivorous>& vec) {
        double min = 100000000;

        for(size_t i = 0; i < vec.size(); ++i)
        {
            if (this != &vec[i] && Technical::Destination(x,y,vec[i].x, vec[i].y) < min && sex != vec[i].sex)
            {
                min = Technical::Destination(x,y,vec[i].x, vec[i].y);
                repAim = std::make_shared<Omnivorous>(vec[i]);
            }
        }
    }


    void reproduct() override {
        satiety -= 500;
        repAim->satiety -= 500;
        repAim->repAim = nullptr;
        repAim = nullptr;
    }

    Omnivorous birth(int birthX, int birthY) {
        Omnivorous baby(birthX, birthY);
        baby.hp = 50;
        baby.satiety = 50;
        baby.speed = 10;
        return baby;
    }

 /*   template<typename...Args>
    void getFoodAim(Args&&... vec) {
        std::vector<std::vector<Object>> v = { vec... };


        double min = 10000000;//Technical::Destination(x,y,v[0][0].x, v[0][0].y);
        foodAim = &v[0][0];
        for (size_t i = 0; i < v.size(); ++i)
            for(size_t j = 0; j < v[i].size(); ++j)
            {
                if (Technical::Destination(x,y,v[i][j].x, v[i][j].y) < min)
                {
                    min = Technical::Destination(x,y,v[i][j].x, v[i][j].y);
                    foodAim = &v[i][j];
                }
            }
    }*/

    template<typename T>
    Object* getFoodAim(std::vector<T> v) {

        double min;
        if(foodAim == nullptr)
        {
            min = 1000000;
            foodAim = &v[0];
        }
        else
            min = Technical::Destination(x,y,foodAim->x, foodAim->y);



        for (size_t i = 0; i < v.size(); ++i)
            if (Technical::Destination(x,y,v[i].x, v[i].y) < min)
            {
                min = Technical::Destination(x,y,v[i].x, v[i].y);
                foodAim = &v[i];
            }

         Object* obj = new Object;
         obj->x = foodAim->x;
         obj->y = foodAim->y;
         obj->isDead = foodAim->isDead;
         obj->ID = foodAim->ID;

         return obj;
    }




    virtual ~Omnivorous() {}
};

//---------------------Environment classes-----------------


class Environment {
public:
    static std::vector<Food> foods;
    static std::vector<differentFood> differentFoods;
    static std::vector<Herbivores> herbs;
    static std::vector<Predators> preds;
    static std::vector<Omnivorous> oms;

    template<typename T>
    static bool checkRepPossibility(T monster, const std::vector<T>& monsterVec) {
        if (monsterVec.size() < 2)
            return false;
        for (int i = 0; i < monsterVec.size(); ++i)
        {
            if (monsterVec[i].sex != monster.sex)
                return true;
        }
            return false;
    }

    /*template<typename T>
    static std::vector<Object> toObject(const std::vector<T>& source) {
        Object newObj;
        std::vector<Object> objVec;
        for (auto i : source) {
              newObj.x = i.x;
              newObj.y = i.y;
              newObj.isDead = i.isDead;
              objVec.push_back(newObj);
        }
        return objVec;
    }*/
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

