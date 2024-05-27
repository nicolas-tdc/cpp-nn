#include "NeuralNetwork.h"
#include <stdlib.h>

NeuralNetwork::NeuralNetwork(
    int inputs_count,
    int layers_count,
    int neurons_per_layer,
    int outputs_count
)
{
    this->inputs_count = inputs_count;
    this->outputs_count = outputs_count;

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
        // Layer n outputs as inputs for layer n+1 or as final layer outputs.
        inputs = layer_outputs;
    }

    return inputs;
}

void NeuralNetwork::backward_propagate(std::vector<double> expected)
{
    for (size_t i = neuron_layers.size(); i >= 0; i--) {

        // Get current layer neurons.
        std::vector<Neuron*>& neurons = neuron_layers[i]->get_neurons();
        for (size_t j = 0; j < neurons.size(); j++) {
            double error {0.0};

            // Initialize error value if in last layer.
            if (i == neuron_layers.size() - 1) {
                error = expected[j] - neurons[j]->get_value();
            }
            else {
                for (Neuron* neuron: neuron_layers[i + 1]->get_neurons()) {
                    // Calculate layer n error value.
                    std::vector<double> weights = neuron->get_weights();
                    double delta = neuron->get_delta();
                    error += weights[j] * delta;
                    // Update layer n+1 weights.
                    weights[j] += learning_rate * delta * neuron->get_value();
                }
            }

            // Update layer n delta.
            double neuron_value = neurons[j]->get_value();
            neurons[j]->set_delta(error * neurons[j]->activator->derive(neuron_value));
        }
    }
}

void NeuralNetwork::train(
    std::vector<std::vector<double>> training_data,
    int epoch_count
)
{
    for (int i = 0; i < epoch_count; i++) {

        for (const std::vector<double>& row: training_data) {
            // Split inputs and expected outputs.
            std::vector<double> inputs(
                row.begin(),
                row.begin() + this->inputs_count
            );
            std::vector<double> expected(
                row.begin() + this->inputs_count,
                row.end()
            );

            // Two-ways propagation.
            this->forward_propagate(inputs);
            this->backward_propagate(expected);
        }
    }
}
