#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <tuple>

int main() {
    std::ifstream in("bmu_mapping.txt");
    if (!in.is_open()) {
        std::cerr << "No se pudo abrir bmu_mapping.txt\n";
        return -1;
    }

    // Mapas para el resumen
    std::map<int, int> total_tests_per_label;
    std::map<int, int> total_bmus_per_label;

    int i, j, k, label, count;
    while (in >> i >> j >> k >> label >> count) {
        total_tests_per_label[label] += count;
        total_bmus_per_label[label]++;
    }

    // Reporte
    std::cout << "Resumen de agrupamientos (etiquetas):\n";
    std::cout << "Etiqueta\tTests asignados\tNeurons (BMUs)\n";
    for (const auto& [label, test_count] : total_tests_per_label) {
        int neuron_count = total_bmus_per_label[label];
        std::cout << label << "\t\t" << test_count << "\t\t" << neuron_count << "\n";
    }

    // Resumen global
    int total_tests = 0;
    for (const auto& [_, count] : total_tests_per_label) {
        total_tests += count;
    }
    std::cout << "\nTotal de tests mapeados: " << total_tests << "\n";

    return 0;
}
