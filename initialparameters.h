#ifndef INITIALPARAMETERS_H
#define INITIALPARAMETERS_H


class InitialParameters
{
public:
    InitialParameters();
    static size_t regFoodsCount;
    static size_t herbsCount;
    static size_t predsCount;
    static size_t omsCount;
    static int simulationSpeed;
    static int herbsSpeed;
    static int predsSpeed;
    static int omsSpeed;
    static int herbsHp;
    static int predsHp;
    static double herbsRepSatiety;
    static double predsRepSatiety;
    static double omsRepSatiety;
    static int minHerbsLifetime;
    static int minPredsLifetime;
    static int minOmsLifetime;
};

#endif // INITIALPARAMETERS_H
