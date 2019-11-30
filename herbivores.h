#ifndef HERBIVORES_H
#define HERBIVORES_H

#include "animal.h"
#include "food.h"
#include <vector>
#include <iostream>


class Herbivores : public Animal
{

public:
    Food *foodAim;
    std::shared_ptr<Herbivores>repAim;
    Herbivores() {}
    Herbivores(int x, int y, int isyoung = 100) {
        this->x = x;
        this->y = y;
        hp =  InitialParameters::herbsHp;
        satiety = 10;
        speed = InitialParameters::herbsSpeed;
        age = rand() % 100 + InitialParameters::minHerbsLifetime;
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
            speed = InitialParameters::herbsSpeed + 3;
            hp = InitialParameters::herbsHp * 0.5;
            satiety = 50;
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
            speed = InitialParameters::herbsSpeed;
        } else
            --young;

        if(danger > 0) {
            speed = InitialParameters::herbsSpeed + 3;
            --danger;
        } else
            speed = InitialParameters::herbsSpeed;

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

        return baby;
    }

    virtual ~Herbivores() {}
};

#endif // HERBIVORES_H
