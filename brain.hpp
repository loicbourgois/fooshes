#pragma once

#include <vector>
#include "neuron.hpp"

class Brain
{
public:
    Brain(int neuronCount, int otherInputCount, std::vector<float> coefficients);
    ~Brain();
    void compute(std::vector<float> &inputs);
    float getOutput(unsigned int id);
private:
    std::vector<Neuron *> neurons;
};
