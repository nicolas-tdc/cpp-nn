#include "Neuron.h"

#include <random>

Neuron::Neuron(int weights_count, ActivatorType activator_type)
{
    activator = new Activator(activator_type);

    // Initialize weights.
    for (int i = 0; i < weights_count - 1; i++) {
        weights.push_back((double) std::rand() / RAND_MAX);
    }
}

Neuron::~Neuron()
{
    // Pass.
}

void Neuron::process(std::vector<double> inputs)
{
    // Initialize value with bias.
    value = bias;
    // Process inputs and weights.
    for (size_t i = 0; i < weights.size() - 2; i++) {
        value += weights[i] * inputs[i];
    }
    // Process value with activation function.
    activator->activate(value);
}
