#include <iostream>
#include <GLFW/glfw3.h>
#include "../include/som/som.h"
#include "../include/opengl/renderer.h"

// Tamaño de ventana
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    // Inicializar GLFW
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SOM 3D Visualization", nullptr, nullptr);
    if (!window) {
        std::cerr << "Error al crear la ventana GLFW\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Cargar pesos
    SOM som(10, 10, 10, 784);
    som.load_weights("../weights_final.txt");

    // Configurar OpenGL
    glEnable(GL_DEPTH_TEST);

    load_bmu_mapping("bmu_mapping.txt");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5, 1.5, -1.5, 1.5, -2.0, 2.0);  // Amplía un poco en Z
    glMatrixMode(GL_MODELVIEW);


    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        static float angle = 0.0f;
        angle += 0.5f;  // Velocidad de rotación

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Rotación para mostrar el cubo en 3D
        glRotatef(angle, 1.0f, 1.0f, 0.0f);

        // Renderizar el SOM
        renderSOM(som);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
