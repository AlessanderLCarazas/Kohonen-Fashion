#include "../include/som/som.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <tuple>

int main() {
    SOM som(10, 10, 10, 784);
    som.load_weights("../weights_final.txt");

    std::ifstream infile("../data/processed/fashion_test.txt");
    if (!infile.is_open()) {
        std::cerr << "No se pudo abrir el archivo de test\n";
        return -1;
    }

    std::map<std::tuple<int, int, int>, std::map<int, int>> neuron_label_count;
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int label;
        iss >> label;

        std::vector<float> vec(784);
        for (auto& v : vec) iss >> v;

        auto bmu = som.find_bmu(vec);
        neuron_label_count[bmu][label]++;
    }

    // Guardar resultado
    std::ofstream out("bmu_mapping.txt");
    for (const auto& [coord, label_map] : neuron_label_count) {
        auto [i, j, k] = coord;
        // Buscar etiqueta dominante
        int max_label = -1;
        int max_count = -1;
        for (const auto& [label, count] : label_map) {
            if (count > max_count) {
                max_count = count;
                max_label = label;
            }
        }
        out << i << " " << j << " " << k << " " << max_label << " " << max_count << "\n";
    }

    std::cout << "BMU mapping guardado en bmu_mapping.txt\n";
    return 0;
}
