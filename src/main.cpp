#include <iostream>
#include <GLFW/glfw3.h>
#include "som/som.h"
#include "opengl/renderer.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    // Inicializar GLFW
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SOM 3D - FashionMNIST", nullptr, nullptr);
    if (!window) {
        std::cerr << "No se pudo crear la ventana GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Inicializar red SOM
    SOM som(10, 10, 10, 784);  // Cubo 10x10x10, vectores de entrada de 784 dimensiones
    som.initialize();          // Inicialización aleatoria

    // Bucle principal de renderizado
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Actualizar entrenamiento (una iteración por frame si deseas verlo animado)
        som.train_step();

        // Dibujar la red de neuronas
        renderSOM(som);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
