#ifndef NEURALTESTS_H
#define NEURALTESTS_H

#include <vector>
#include <cstdlib>
#include <cmath>
#include <chrono>

#include "network.h"

class NeuralTests
{
public:
    NeuralTests();

    static void testInit();
    static void testAND(int count, int transfertType = SIGMOID);
    static void testOR(int count, int transfertType = SIGMOID);
    static void testXOR(int count, int transfertType = SIGMOID);

    static void compareTransfert(int count);
};

#endif // NEURALTESTS_H
