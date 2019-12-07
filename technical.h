#ifndef TECHNICAL_H
#define TECHNICAL_H

#include <cmath>
#include "initialparameters.h"

class Technical {
public:
    Technical();
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
#endif // TECHNICAL_H
