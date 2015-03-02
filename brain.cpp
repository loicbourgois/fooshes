#include "brain.h"

#include <QDebug>


Brain::Brain(int neuronCount, int otherInputCount, std::vector<float> coefficients)
{
    int totalInputPerNeuron = neuronCount + otherInputCount;
    unsigned int totalInput = totalInputPerNeuron * neuronCount;
    if(coefficients.size() != totalInput)
    {
        qDebug() << " pas meme ";
    }
    else
    {
        for(int i = 0 ; i < neuronCount ; i++)
        {
            std::vector<float> coefs(&coefficients[i * totalInputPerNeuron], &coefficients[(i+1) * totalInputPerNeuron]);
            neurons.push_back(new Neuron(coefs, totalInputPerNeuron));
        }
    }
}

Brain::~Brain()
{
    for(unsigned int i = 0 ; i < neurons.size() ; i++)
    {
        delete neurons[i];
    }
    neurons.clear();
}

void Brain::compute(std::vector<float> & inputs)
{
    for(unsigned int i = 0 ; i < neurons.size() ; i++)
    {
        inputs.push_back(neurons[i]->getOutput());
    }

    for(unsigned int i = 0 ; i < neurons.size() ; i++)
    {
        neurons[i]->compute(inputs);
    }
}

float Brain::getOutput(int id)
{
    float output = neurons[id]->getOutput();
    return output;
}

