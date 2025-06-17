#ifndef SOM_H
#define SOM_H

#include <vector>
#include <random>
#include <tuple>

class SOM {
private:
    int m, n, o;              // Dimensiones del cubo 3D
    int input_dim;           // Dimensión de los vectores de entrada
    float alpha;             // Tasa de aprendizaje
    float radius;            // Radio de vecindad
    int epoch;

    struct Neuron {
        std::vector<float> weights;
        int i, j, k;  // posición en el cubo
    };

    std::vector<Neuron> neurons;
    std::vector<std::vector<float>> training_data;

public:
    SOM(int m_, int n_, int o_, int input_dim_);
    void initialize();
    void load_data(const std::string& filepath);
    void train_step();
    std::tuple<int,int,int> find_bmu(const std::vector<float>& input);
    const std::vector<Neuron>& get_neurons() const;
    void save_weights(const std::string& filename);
    void load_weights(const std::string& filename);

};

#endif
