#ifndef BRAIN_H
#define BRAIN_H

#include <vector>
#include "neuron.h"

class Brain
{
public:
    Brain(int neuronCount, int otherInputCount, std::vector<float> coefficients);
    ~Brain();
    void compute(std::vector<float> &inputs);
    float getOutput(int id);
private:
    std::vector<Neuron *> neurons;
};

#endif // BRAIN_H
