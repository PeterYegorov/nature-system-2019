#ifndef FOOD_H
#define FOOD_H

#include "technical.h"
#include "object.h"


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

#endif // FOOD_H
