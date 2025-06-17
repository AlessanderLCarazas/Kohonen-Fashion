#include "../include/opengl/renderer.h"
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <tuple>

std::map<std::tuple<int, int, int>, int> neuron_colors;

void load_bmu_mapping(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << filename << "\n";
        return;
    }

    int i, j, k, label, count;
    while (in >> i >> j >> k >> label >> count) {
        neuron_colors[{i, j, k}] = label;
    }
}

void setColorForLabel(int label) {
    switch (label) {
        case 0: glColor3f(1, 0, 0); break;       // rojo
        case 1: glColor3f(0, 1, 0); break;       // verde
        case 2: glColor3f(0, 0, 1); break;       // azul
        case 3: glColor3f(1, 1, 0); break;       // amarillo
        case 4: glColor3f(1, 0, 1); break;       // magenta
        case 5: glColor3f(0, 1, 1); break;       // cian
        case 6: glColor3f(1, 1, 1); break;       // blanco
        case 7: glColor3f(1, 0.5, 0); break;     // naranja
        case 8: glColor3f(1, 0.75, 0.8); break;  // rosa
        case 9: glColor3f(0.5, 0.5, 0.5); break; // gris
        default: glColor3f(0.3, 0.3, 0.3); break; // desconocido
    }
}

void renderSOM(const SOM& som) {
    const auto& neurons = som.get_neurons();
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (const auto& neuron : neurons) {
        auto key = std::make_tuple(neuron.i, neuron.j, neuron.k);
        if (neuron_colors.find(key) != neuron_colors.end()) {
            setColorForLabel(neuron_colors[key]);
        } else {
            glColor3f(0.3f, 0.3f, 0.3f);  // Sin test asignado
        }

        float x = (float)neuron.i / 10.0f * 2.0f - 1.0f;
        float y = (float)neuron.j / 10.0f * 2.0f - 1.0f;
        float z = (float)neuron.k / 10.0f * 2.0f - 1.0f;

        glVertex3f(x, y, z);
    }
    glEnd();
}

void renderLegend() {
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 10; ++i) {
        setColorForLabel(i);
        float x = -0.95f;  // Cerca de la esquina
        float y = 0.9f - i * 0.05f;
        glVertex2f(x, y);
    }
    glEnd();
}
