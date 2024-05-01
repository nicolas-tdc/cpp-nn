#pragma once

enum class ActivatorType {
    Sigmoid,
    ReLu,
    Tanh
};

class Activator {

private:
    ActivatorType type;

public:
    Activator(ActivatorType activator_type);
    ~Activator();

    void activate(double& input);
    void derive(double& input);
};