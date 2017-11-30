#include "neuraltests.h"

NeuralTests::NeuralTests()
{

}

void NeuralTests::testInit()
{
    std::vector<int> topology = {2,4,4,1};
    Network *n = new Network(topology);

    std::cout<< n->getInfo() << std::endl;

    delete n;
}

void NeuralTests::testAND(int count, int transfertType)
{
    std::vector<std::vector<float>> inputs;
    std::vector<std::vector<float>> targets;

    for(int i=0;i<count;i++)
    {
        int a = rand() % 2;
        int b = rand() % 2;
        int s = (int)(a == b);

        std::vector<float> in = {(float)a, (float)b};
        std::vector<float> out = {(float)s};
        inputs.push_back(in);
        targets.push_back(out);
    }

    std::vector<int> topology = {2, 4, 4, 1};
    Network *n = new Network(topology, transfertType);
    n->backPropBatch(inputs, targets);

    for(int a=0; a<2; a++)
    {
        for(int b=0; b<2; b++)
        {
            std::vector<float> in = {(float)a, (float)b};
            float s = n->process(in)[0];
            std::cout << a << " AND " << b << " = " << s << std::endl;
        }
    }
}

void NeuralTests::testOR(int count, int transfertType)
{

}

void NeuralTests::testXOR(int count, int transfertType)
{

}

void NeuralTests::compareTransfert(int count)
{
    //Sigmoid
    auto begin = std::chrono::high_resolution_clock::now();
    NeuralTests::testAND(count, SIGMOID);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Sigmoid : " << std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count() << "ms" << std::endl;

    //RELU
    begin = std::chrono::high_resolution_clock::now();
    NeuralTests::testAND(count, RELU);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "ReLU : " << std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count() << "ms" << std::endl;

    //Smooth RELU
    begin = std::chrono::high_resolution_clock::now();
    NeuralTests::testAND(count, SMOOTH_RELU);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Smooth ReLU : " << std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count() << "ms" << std::endl;
}
