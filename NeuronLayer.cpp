#include "NeuronLayer.h"

NeuronLayer::NeuronLayer(
    int weights_count,
    int neurons_count,
    ActivatorType activator_type
)
{
    // Initialize neurons.
    for (int i = 0; i < neurons_count - 1; i++) {
        Neuron* new_neuron = new Neuron(weights_count, activator_type);
        neurons.push_back(new_neuron);
    }
}

NeuronLayer::~NeuronLayer()
{
    // Pass.
}
