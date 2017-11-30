#ifndef NETWORK_H
#define NETWORK_H

#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>

enum TransferFunction
{
    SIGMOID = 0,
    RELU,
    SMOOTH_RELU
};

class Network
{
public:
    Network(std::vector<int> topology, int transfertType = SIGMOID);
    void init(std::vector<int> topology, int transfertType = SIGMOID);

    std::vector<float> process(std::vector<float> inputs);

    void setRandomWeights();
    void setWeights(std::vector<float> weights);
    void setInputs(std::vector<float> inputs);
    void feedForward();
    float backProp(std::vector<float> inputs, std::vector<float> targets);
    float backPropBatch(std::vector<std::vector<float>> inputs, std::vector<std::vector<float>> targets);

    std::vector<float> getOutputs();
    std::string getInfo();
    float getRecentAverageError();

    static float activationFunction(float x, int transfertType = SIGMOID);
    static float calcOutGradients(float target, float value, int transfertType = SIGMOID);
    static float calcGradient(float value, std::vector<float> neuronWeights, std::vector<float> nextLayerGradients, int transfertType = SIGMOID);
    static float transferFunctionDerivative(float x, int transfertType = SIGMOID);
    static float sumDOW(std::vector<float> neuronWeights, std::vector<float> nextLayerGradients);

private:
    int transfertType = SIGMOID;

    unsigned neuronCount = 0;
    unsigned weightCount = 0;
    unsigned layerCount = 0;

    //BackProp
    float recentAvgError = 0.0f;
    float recentAvgSmoothingFactor = 100.0f;
    float eta = 0.15f;
    float alpha = 0.5f;

    std::vector<int> topology;

    std::vector<std::vector<float>> values;
    std::vector<std::vector<float>> gradients;

    std::vector<std::vector<std::vector<float>>> weights;
    std::vector<std::vector<std::vector<float>>> deltaWeights;
};

#endif // NETWORK_H
