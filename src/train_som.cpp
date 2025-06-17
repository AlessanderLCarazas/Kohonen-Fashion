#include "../include/som/som.h"
#include <iostream>

int main() {
    // Configuración del SOM
    const int m = 10;
    const int n = 10;
    const int o = 10;
    const int input_dim = 784;
    const int num_epochs = 10000;  // Puedes ajustar este número

    SOM som(m, n, o, input_dim);

    std::cout << "Inicializando la red...\n";
    som.initialize();

    std::cout << "Cargando datos de entrenamiento...\n";
    som.load_data("../data/processed/fashion_train.txt");

    std::cout << "Entrenando SOM con " << num_epochs << " pasos...\n";
    for (int i = 0; i < num_epochs; ++i) {
        som.train_step();
    }

    std::cout << "Guardando pesos finales...\n";
    som.save_weights("../weights_final.txt");

    std::cout << "Entrenamiento finalizado.\n";
    return 0;
}
