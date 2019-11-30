#ifndef OMNIVOROUS_H
#define OMNIVOROUS_H

#include "predators.h"

class Omnivorous : public Animal {
public:
    Omnivorous() {}
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

#endif // OMNIVOROUS_H
