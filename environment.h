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
#endif // ENVIRONMENT_H
