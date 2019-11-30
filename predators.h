#ifndef PREDATORS_H
#define PREDATORS_H

#include "herbivores.h"

class Predators : public Animal {

public:
    Herbivores *foodAim;
    std::shared_ptr<Predators> repAim;
    Predators() {}

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

        if(Technical::allHerbsDied){
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


#endif // PREDATORS_H
