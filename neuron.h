#pragma once

#include <QObject>
#include <vector>

class Neuron
{
public:
    Neuron(std::vector<float> coefficients, unsigned int inputCount);
    float getOutput();
    void compute(std::vector<float> inputValues);
private:
    std::vector<float> coefficients;
    float outputValue;
};
