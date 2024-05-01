#include "Activator.h"
#include <cmath>

Activator::Activator(ActivatorType activator_type)
{
    type = activator_type;
}

Activator::~Activator()
{
    // Pass.
}

void Activator::activate(double& input)
{
    switch (type)
    {
    case ActivatorType::Sigmoid:
        input = 1.0f / (1.0f + std::exp(input));
        break;

    case ActivatorType::ReLu:
        if (input < 0) {
            input = 0;
        }
        break;

    case ActivatorType::Tanh:
        input = tanh(input);
        break;

    default:
        break;
    }
}

void Activator::derive(double& input)
{
    switch (type)
    {
    case ActivatorType::Sigmoid:
        activate(input);
        input = input * (1.0f - input);
        break;

    case ActivatorType::ReLu:
        if (input > 0) {
            input = 1;
        }

        input = 0;
        break;

    case ActivatorType::Tanh:
        input = 1 - tanh(input) * tanh(input);
        break;
    
    default:
        break;
    }
}
