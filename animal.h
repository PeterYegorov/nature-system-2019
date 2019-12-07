#ifndef ANIMAL_H
#define ANIMAL_H

#include "object.h"

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

    virtual void move() = 0;
    virtual void eat() = 0;
    virtual void reproduce() = 0;
    virtual void die() = 0;
};

#endif // ANIMAL_H
