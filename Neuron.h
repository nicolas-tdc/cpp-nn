#pragma once

#include "Activator.h"
#include <vector>

class Neuron {

private:
    int weights_count;
    std::vector<double> weights;
    double bias {0};

    double value {0};
    double error_delta {0};

public:
    Neuron(int weights_count, ActivatorType activator_type);
    ~Neuron();

    Activator* activator;

    std::vector<double> get_weights(void) { return weights; }
    double get_bias(void) { return bias; }
    double get_value(void) { return value; }
    double get_delta(void) { return error_delta; }
    void set_delta(double delta) { error_delta = delta; }

    void process(std::vector<double> inputs);
};