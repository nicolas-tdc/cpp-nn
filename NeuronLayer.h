#pragma once

#include "Neuron.h"
#include "Activator.h"
#include <vector>

class NeuronLayer {

private:
    std::vector<Neuron*> neurons;

public:
    NeuronLayer(
        int neurons_count,
        int weights_count,
        ActivatorType activator_type
    );
    ~NeuronLayer();

    std::vector<Neuron*>& get_neurons(void) { return neurons; }
};
