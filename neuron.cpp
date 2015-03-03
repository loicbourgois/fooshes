#include "neuron.hpp"

#include <QDebug>

Neuron::Neuron(std::vector<float> coefficients, unsigned int inputCount)
{
    if(coefficients.size() != inputCount)
        qDebug() << "Problem in neuron : inputCount != coefficientCount";
    this->coefficients = coefficients;
    outputValue = coefficients[0];
}

float Neuron::getOutput()
{
    return outputValue;
}

void Neuron::compute(std::vector<float> inputValues)
{
    if(inputValues.size() == coefficients.size())
    {
        float divisor = 0.0f;
        outputValue = 0;
        for(unsigned int i = 0 ; i < inputValues.size() ; i++)
        {
            if(inputValues[i]>1 || inputValues[i]<-1)
                qDebug() << "Input value >  < 1 : " << inputValues[i];
            outputValue += inputValues[i] * coefficients[i];
            divisor += fabs(coefficients[i]);
        }
        outputValue /= divisor;
        if(outputValue>1 || outputValue<-1)
            qDebug() << "output value >  < 1 : " << outputValue;
    }
    else
        qDebug() << "Coefficient count not matching inputs.";
}
