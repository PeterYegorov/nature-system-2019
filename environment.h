#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "mainwindow.h"
#include "omnivorous.h"
class Environment {
public:
    Environment() {}
    static std::vector<Food> foods;
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
};
#endif // ENVIRONMENT_H
