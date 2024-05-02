#pragma once

#include "Neuron.h"
#include "Activator.h"
#include <vector>

class NeuronLayer {

private:
    std::vector<Neuron*> neurons;

public:
    NeuronLayer(
        int weights_count,
        int neurons_count,
        ActivatorType activator_type
    );
    ~NeuronLayer();

    std::vector<Neuron*>& get_neurons(void) { return neurons; }
};
