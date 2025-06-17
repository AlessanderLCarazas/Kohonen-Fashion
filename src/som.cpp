#include "som/som.h"
#include <cmath>
#include <limits>
#include <fstream>
#include <sstream>
#include <iostream>

SOM::SOM(int m_, int n_, int o_, int input_dim_)
    : m(m_), n(n_), o(o_), input_dim(input_dim_), alpha(0.1f), radius(3.0f), epoch(0) {}

// Inicializar pesos aleatorios y asignar coordenadas
void SOM::initialize() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    neurons.clear();
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < o; ++k) {
                Neuron neuron;
                neuron.i = i;
                neuron.j = j;
                neuron.k = k;
                neuron.weights.resize(input_dim);
                for (int d = 0; d < input_dim; ++d)
                    neuron.weights[d] = dist(gen);
                neurons.push_back(neuron);
            }
}

// Cargar datos desde archivo .txt con formato: etiqueta valor1 valor2 ...
void SOM::load_data(const std::string& filepath) {
    training_data.clear();
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo de datos: " << filepath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<float> vec;
        float value;
        int label;
        ss >> label;  // ignorar etiqueta, pero se podría guardar si se desea
        while (ss >> value)
            vec.push_back(value);
        if (vec.size() == input_dim)
            training_data.push_back(vec);
    }

    std::cout << "Datos cargados: " << training_data.size() << " vectores." << std::endl;
}

// Encuentra la neurona más cercana (Best Matching Unit)
std::tuple<int, int, int> SOM::find_bmu(const std::vector<float>& input) {
    float min_dist = std::numeric_limits<float>::max();
    std::tuple<int, int, int> bmu_idx;

    for (const auto& neuron : neurons) {
        float dist = 0.0f;
        for (int d = 0; d < input_dim; ++d)
            dist += std::pow(input[d] - neuron.weights[d], 2);
        if (dist < min_dist) {
            min_dist = dist;
            bmu_idx = {neuron.i, neuron.j, neuron.k};
        }
    }

    return bmu_idx;
}

// Función de vecindad gaussiana
float gaussian(float dist, float sigma) {
    return std::exp(-dist * dist / (2 * sigma * sigma));
}

// Entrenamiento por un paso (una muestra aleatoria)
void SOM::train_step() {
    if (training_data.empty()) return;

    // Tomar vector aleatorio de training data
    // 'input'
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<size_t> dis(0, training_data.size() - 1);
    const auto& input = training_data[dis(gen)];

    // Encontrar neurona con peso más similar 
    // al vector seleccionado 'input'
    auto [bi, bj, bk] = find_bmu(input);

    // Actualizar cada neurona
    for (auto& neuron : neurons) {
        float dx = bi - neuron.i;
        float dy = bj - neuron.j;
        float dz = bk - neuron.k;
        float dist = std::sqrt(dx * dx + dy * dy + dz * dz);

        // Evaluar distancia
        if (dist <= radius) {
            float h = gaussian(dist, radius); // influencia de vecindad
            for (int d = 0; d < input_dim; ++d) {
                neuron.weights[d] += alpha * h * (input[d] - neuron.weights[d]);
            }
        }
    }

    // Decaimiento gradual
    epoch++;
    alpha *= 0.995f;    // Disminuye lentamente
    radius *= 0.995f;

    std::cout << "Epoch " << epoch << " alpha: " << alpha << " radius: " << radius << "\n";

}

// Devuelve las neuronas (para visualización)
const std::vector<SOM::Neuron>& SOM::get_neurons() const {
    return neurons;
}

void SOM::save_weights(const std::string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "No se pudo abrir el archivo para guardar pesos: " << filename << "\n";
        return;
    }

    for (const auto& neuron : neurons) {
        out << neuron.i << " " << neuron.j << " " << neuron.k;
        for (const auto& w : neuron.weights)
            out << " " << w;
        out << "\n";
    }

    out.close();
    std::cout << "Pesos guardados completos en: " << filename << "\n";
}


void SOM::load_weights(const std::string& filename) {
    neurons.clear();
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "No se pudo abrir el archivo de pesos: " << filename << "\n";
        return;
    }
    int i, j, k;
    while (in >> i >> j >> k) {
        Neuron neuron;
        neuron.i = i;
        neuron.j = j;
        neuron.k = k;
        neuron.weights.resize(input_dim);
        for (auto& w : neuron.weights)
            in >> w;
        neurons.push_back(neuron);
    }
    in.close();
    std::cout << "Pesos cargados: " << neurons.size() << " neuronas.\n";
}

