#pragma once

#include "NeuronLayer.h"
#include "Activator.h"
#include <vector>

class NeuralNetwork {

private:
    int layers_count {0};
    double learning_rate {0.01};
    std::vector<NeuronLayer> NeuronLayers;

public:
    NeuralNetwork();
    ~NeuralNetwork();

    void add_layer(
        int neurons_count,
        int weights_count,
        ActivatorType activator_type
    );

    std::vector<double> forward_propagate(std::vector<double> inputs);
    void backward_propagate(std::vector<double> expected);

    void train(
        std::vector<std::vector<float>> training_data,
        int epoch_count,
        int outputs_count
    );

};
