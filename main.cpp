#include <stdlib.h>
#include "NeuralNetwork.h"

int main()
{
    // Define network parameters.
    int inputs_count {4};
    int layers_count {8};
    int neurons_per_layer {512};
    int outputs_count {2};
    int epochs_count {100};

    // Generate random training data.
    std::vector<std::vector<double>> training_data = generate_random_training_data(
        inputs_count + outputs_count
    );

    // Initialize network.
    NeuralNetwork* network = new NeuralNetwork(
        inputs_count,
        layers_count,
        neurons_per_layer,
        outputs_count
    );

    network->train(training_data, epochs_count);

    // Predict for specific inputs.
    std::vector<double> predicted = network->forward_propagate({5, 129, 8, 43});
}

std::vector<std::vector<double>> generate_random_training_data(int data_per_row) {
    int training_data_count {200};
    std::vector<std::vector<double>> training_data;
    for (int i = 0; i < training_data_count; i++) {

        std::vector<double> training_data_row;
        for (int j = 0; j < (data_per_row - 1); j++) {
            training_data_row.emplace_back(rand());
        }

        training_data.emplace_back(training_data_row);
    }

    return training_data;
}

double generate_random_double(double min, double max)
{
    double normalized_rand = (double)rand() / RAND_MAX;

    return min + normalized_rand * (max - min);
}
