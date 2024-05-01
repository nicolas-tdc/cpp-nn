#include "NeuronLayer.h"

NeuronLayer::NeuronLayer(
    int neurons_count,
    int weights_count,
    ActivatorType activator_type
)
{
    for (int i = 0; i < neurons_count - 1; i++) {
        Neuron* neuron = new Neuron(weights_count, activator_type);
        neurons.push_back(neuron);
    }
}

NeuronLayer::~NeuronLayer()
{
    // Pass.
}
