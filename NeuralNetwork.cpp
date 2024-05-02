#include "NeuralNetwork.h"
#include <stdlib.h>

NeuralNetwork::NeuralNetwork(
    int inputs_count,
    int layers_count,
    int neurons_per_layer,
    int outputs_count
)
{
    // Add input layer.
    add_layer(inputs_count, neurons_per_layer, ActivatorType::Sigmoid);
    // Add hidden layers.
    for (int i = 0; i < layers_count; i++) {
        add_layer(neurons_per_layer, neurons_per_layer, ActivatorType::ReLu);
    }
    // Add output layer.
    add_layer(neurons_per_layer, outputs_count, ActivatorType::Sigmoid);
}

NeuralNetwork::~NeuralNetwork()
{
    // Pass.
}

void NeuralNetwork::add_layer(
    int weights_count,
    int neurons_count,
    ActivatorType activator_type
)
{
    NeuronLayer* new_layer = new NeuronLayer(
        weights_count, neurons_count, activator_type
    );
    neuron_layers.push_back(new_layer);
}

std::vector<double> NeuralNetwork::forward_propagate(std::vector<double> inputs)
{
    for (size_t i = 0; i < neuron_layers.size(); i++) {
        std::vector<double> layer_outputs {};

        std::vector<Neuron*> neurons = neuron_layers[i]->get_neurons();
        for (size_t j = 0; j < neurons.size(); j++) {
            neurons[j]->process(inputs);
            layer_outputs.push_back(neurons[j]->get_value());
        }

        inputs = layer_outputs;
    }

    return inputs;
}

void NeuralNetwork::backward_propagate(std::vector<double> expected)
{
    for (size_t i = neuron_layers.size(); i >= 0; i--) {

        std::vector<Neuron*>& neurons = neuron_layers[i]->get_neurons();
        for (size_t j = 0; j < neurons.size(); j++) {
            double error {0.0};

            if (i == neuron_layers.size() - 1) {
                error = expected[j] - neurons[j]->get_value();
            }
            else {
                for (Neuron* neuron: neuron_layers[i + 1]->get_neurons()) {
                    error += neuron->get_weights()[j] * neuron->get_delta();
                }
            }

            double neuron_value = neurons[j]->get_value();
            neurons[j]->set_delta(error * neurons[j]->activator->derive(neuron_value));
        }
    }
}
