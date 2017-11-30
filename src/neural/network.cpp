#include "network.h"

Network::Network(std::vector<int> topology, int transfertType)
{
    this->init(topology, transfertType);
}

void Network::init(std::vector<int> topology, int transfertType)
{
    this->transfertType = transfertType;

    this->topology = topology;
    this->layerCount = topology.size();

    this->values.resize(this->layerCount);
    this->gradients.resize(this->layerCount);
    this->weights.resize(this->layerCount);
    this->deltaWeights.resize(this->layerCount);

    //Values
    this->neuronCount = 0;
    for(unsigned i=0;i<this->layerCount;i++)
    {
        int nNodes = topology[i];
        this->values[i].resize(nNodes);
        std::fill(this->values[i].begin(), this->values[i].end(), 0.0f);

        //For each hidden layer, we put one less gradient than there is nodes due to the bias node
        int nGrad = (i > 0 && i < this->layerCount - 1) ? nNodes - 1 : nNodes;
        this->gradients[i].resize(nGrad);
        std::fill(this->gradients[i].begin(), this->gradients[i].end(), 0.0f);

        this->neuronCount += nNodes;
    }

    //Weights
    this->weightCount = 0;
    for(unsigned i=0;i<this->layerCount-1;i++)
    {
        int nNodes = topology[i];
        this->weights[i].resize(nNodes);
        this->deltaWeights[i].resize(nNodes);

        for(int j=0; j<nNodes; j++)
        {
            unsigned nLC = (i == this->layerCount - 2) ? this->topology[i+1] : this->topology[i+1] - 1; // NextLayer Count
            this->weights[i][j].resize(nLC);
            this->deltaWeights[i][j].resize(nLC);

            std::fill(this->weights[i][j].begin(), this->weights[i][j].end(), 0.0f);
            std::fill(this->deltaWeights[i][j].begin(), this->deltaWeights[i][j].end(), 0.0f);


            this->weightCount += nLC;
        }
    }

    this->setRandomWeights();
}

void Network::setRandomWeights()
{
    std::vector<float> weights;

    for(int i=0; i<this->weightCount; i++)
    {
        float r = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2.0f - 1.0f;
        weights.push_back(r);
    }

    this->setWeights(weights);
}

void Network::setWeights(std::vector<float> weights)
{
    if(weights.size() != this->weightCount)
    {
        std::cerr << "Number of weights mismatches. Tried to assign " << weights.size() << ", expected " << this->weightCount << std::endl;
    }
    else
    {
        int c = 0;
        for (unsigned i = 0; i < this->weights.size(); i++)
        {
            for (unsigned j = 0; j < this->weights[i].size(); j++)
            {
                for (unsigned k = 0; k < this->weights[i][j].size(); k++)
                {
                    this->weights[i][j][k] = weights[c];
                    c++;
                }
            }
        }
    }
}

std::string Network::getInfo()
{
    std::ostringstream oss;
    oss << "Network has " << this->values.size() << " layers, " << this->neuronCount << " Neurons and " << this->weightCount << " weights.";
    return oss.str();
}

std::vector<float> Network::process(std::vector<float> inputs)
{
    this->setInputs(inputs);
    this->feedForward();
    return this->getOutputs();
}

void Network::setInputs(std::vector<float> inputs)
{
    if(inputs.size() == this->values[0].size())
    {
        this->values[0] = inputs;
    }
    else
    {
        std::cerr << "Input count mismatch. Expected " << this->values[0].size() << ", but got " << inputs.size() << std::endl;
    }

}

void Network::feedForward()
{
    //Process hidden layers
    for(unsigned cLayer = 1; cLayer < this->layerCount; cLayer++)
    {
        //Get the previous layer length
        unsigned prevLayerLength = this->topology[cLayer-1];

        //Get the current layer length, excluding bias node (they are not fed)
        unsigned currLayerLength = cLayer >= 1 && cLayer < this->layerCount - 1 ? this->topology[cLayer] - 1 : this->topology[cLayer];

        //For each node in the current layer
        for(unsigned cNode = 0; cNode<currLayerLength; cNode++)
        {
            float sum = 0.0;
            //For each node in the previosu layer
            for (unsigned cNodePrev = 0; cNodePrev<prevLayerLength; cNodePrev++)
            {
                //Sum all the val*weight of previous nodes to the current node
                sum += this->values[cLayer - 1][cNodePrev] * this->weights[cLayer - 1][cNodePrev][cNode];
            }

            //Apply the transfer function (TanH)
            this->values[cLayer][cNode] = activationFunction(sum, this->transfertType);
        }
    }
}

float Network::activationFunction(float x,int transfertType)
{
    switch(transfertType)
    {
    case SIGMOID:
        return (float)tanh(x);
        break;
    case RELU:
        return x > 0.0f ? x : 0.0f;
        break;
    case SMOOTH_RELU:
        return (float)log(1.0 + exp(x));
        break;
    default:
        return 1.0f;
    }
}

float Network::backProp(std::vector<float> inputs, std::vector<float> targets)
{
    // Calculate overall net error (RMS of output errors)
    unsigned outLayer = this->layerCount - 1;
    unsigned outCount = this->topology[outLayer];

    float error = 0.0f;

    std::vector<float> o = this->process(inputs);

    for (unsigned n=0;n<outCount; n++)
    {
        float delta = targets[n] - o[n];
        error += delta * delta;
    }

    error /= outCount; //Get average error squared
    error = sqrt(error); //RMS

    //Implement a recent average measurement :
    recentAvgError = (recentAvgError * recentAvgSmoothingFactor + error) / (recentAvgSmoothingFactor + 1.0);

    //Calculate output layer gradients
    for (unsigned n = 0; n < outCount; n++)
    {
        this->gradients[outLayer][n] = (float)calcOutGradients(targets[n], values[outLayer][n], this->transfertType);
    }

    //Calculate on hidden layers
    for (unsigned layer = this->layerCount - 2; layer > 0; --layer)
    {
        unsigned layerNext = layer+1;

        for (unsigned n = 0; n < topology[layer]-1; ++n)
        {
            gradients[layer][n] = calcGradient(values[layer][n], weights[layer][n], gradients[layerNext], this->transfertType);
        }
    }

    // For all layers from output to first hidden layer,
    // update connection weights
    for (unsigned layer = this->layerCount - 1; layer > 0; --layer)
    {
        unsigned layerPrev = layer - 1;
        unsigned layerLength = layer >= 1 && layer < this->layerCount - 1 ? this->topology[layer] - 1 : this->topology[layer];
        unsigned prevLayerLength = layerPrev >= 1 && layerPrev < this->layerCount - 1 ? this->topology[layerPrev] - 1 : this->topology[layerPrev];

        for (unsigned n = 0; n < layerLength; n++)
        {
            for(unsigned m = 0; m < prevLayerLength; m++)
            {
                float d = this->deltaWeights[layerPrev][m][n];
                this->deltaWeights[layerPrev][m][n] =
                    //Individual input, magnified by the gradient and train rate
                    this->eta
                    * this->values[layerPrev][m]
                    * this->gradients[layer][n]
                    //Also add momentum = a fraction of the previous delta weight
                    + this->alpha
                    * d;
                this->weights[layerPrev][m][n] += this->deltaWeights[layerPrev][m][n];
            }
        }
    }

    return this->recentAvgError;
}

float Network::backPropBatch(std::vector<std::vector<float>> inputs, std::vector<std::vector<float>> targets)
{
    for(unsigned i=0; i<inputs.size(); i++)
    {
        this->backProp(inputs[i], targets[i]);
    }

    return this->recentAvgError;
}

std::vector<float> Network::getOutputs()
{
    return this->values[this->values.size()-1];
}

float Network::calcOutGradients(float target, float value, int transfertType)
{
    return (target - value) * transferFunctionDerivative(value, transfertType);
}

float Network::calcGradient(float value, std::vector<float> neuronWeights, std::vector<float> nextLayerGradients, int transfertType)
{
    return sumDOW(neuronWeights, nextLayerGradients) * transferFunctionDerivative(value, transfertType);
}

float Network::transferFunctionDerivative(float x, int transfertType)
{
    switch(transfertType)
    {
    case SIGMOID:
        return 1.0f - (x*x);
        break;
    case RELU:
        return x > 0 ? 1 : 0;
        break;
    case SMOOTH_RELU:
        return (float)tanh(x);
        break;
    default:
        return 1.0f;
    }
}

float Network::sumDOW(std::vector<float> neuronWeights, std::vector<float> nextLayerGradients)
{
    float sum = 0.0f;

    //Sum our contributions of the errors at the nodes we feed

    for (unsigned n = 0; n < nextLayerGradients.size(); n++)
    {
        sum += neuronWeights[n] * nextLayerGradients[n];
    }

    return sum;
}

float Network::getRecentAverageError()
{
    return this->recentAvgError;
}
