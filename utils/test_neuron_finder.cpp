#include "../include/som/som.h"
#include <iostream>

int main() {
    SOM som(10, 10, 10, 784); // Cubo 10x10x10 y vectores de 784 dimensiones
    som.initialize();
    som.load_data("../data/processed/fashion_train.txt");

    std::cout << "Entrenando con 100 pasos...\n";
    for (int i = 0; i < 100; ++i) {
        som.train_step();
    }

    std::cout << "Buscando la BMU del primer vector...\n";
    const auto& data = som.get_neurons(); // accede a la red solo por verificación
    auto bmu = som.find_bmu(som.get_neurons()[0].weights);

    auto [i, j, k] = bmu;
    std::cout << "BMU encontrada en coordenadas: (" << i << ", " << j << ", " << k << ")\n";

    std::cout << "Guardando pesos finales...\n";
    som.save_weights("weights_final.txt");

    return 0;
}
