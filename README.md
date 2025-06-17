# Kohonen-Fashion



# SOM3D_Fashion

Este proyecto implementa un **Mapa Autoorganizado (Self-Organizing Map, SOM)** tridimensional para el análisis y visualización de datos de moda (Fashion MNIST). Utiliza C++ con OpenGL para la visualización y CMake como sistema de construcción. Su objetivo principal es entrenar un SOM con vectores de entrada de alta dimensión y visualizar cómo se organizan topológicamente en un espacio 3D.

---

##  Objetivo del Proyecto

Entrenar y visualizar un mapa autoorganizado tridimensional con datos de alta dimensión, permitiendo:

- Agrupación no supervisada (clustering) de muestras visuales.
- Exploración interactiva del comportamiento de un SOM en 3D.
- Observación de cómo se organizan espacialmente los pesos neuronales.

---

## Flujo del Proyecto

1. **Entrenamiento (`train_som`)** 
   - Inicializa una red de neuronas 3D con pesos aleatorios.
   - Lee el dataset (preprocesado como vectores numéricos).
   - Ejecuta el entrenamiento SOM: búsqueda del BMU (Best Matching Unit), ajuste de pesos, y actualización del radio y tasa de aprendizaje.
   - Guarda los pesos entrenados en `weights_final.txt`.

2. **Mapeo (`test_mapper`)** 
   - Usa los pesos entrenados.
   - Asigna cada vector de entrada a su neurona BMU.
   - Guarda el mapeo en `bmu_mapping.txt`.

3. **Visualización (`visualize_som`)** 
   - Carga los pesos entrenados.
   - Visualiza el SOM tridimensional con OpenGL.
   - Cada neurona se representa como un cubo coloreado o etiquetado según el BMU asignado.

---

##  Estructura de Carpetas

```
SOM3D_Fashion/
│
├── CMakeLists.txt              # Archivo principal para construir el proyecto con CMake
├── README.md                   # Instrucciones y documentación
├── weights_final.txt           # Pesos entrenados finales del SOM
│
├── build/                      # Archivos generados por CMake y binarios compilados
│   ├── train_som               # Ejecutable para entrenamiento
│   ├── test_mapper             # Ejecutable para asignar vectores a neuronas
│   ├── visualize_som           # Ejecutable para visualizar la red SOM
│   └── ...
```

---

##  Instalación y Compilación

### Requisitos

- CMake ≥ 3.10
- Compilador C++ (GCC o Clang)
- OpenGL y GLUT instalados (para `visualize_som`)

### Pasos

```bash
# 1. Clonar el repositorio o extraer el ZIP
cd SOM3D_Fashion

# 2. Crear carpeta de construcción
mkdir build && cd build

# 3. Configurar con CMake
cmake ..

# 4. Compilar
make
```

---

##  Ejecución

### Entrenar el SOM

```bash
./train_som
```

### Mapear entradas a neuronas

```bash
./test_mapper
```

### Visualizar en 3D

```bash
./visualize_som
```

---

##  Archivos Importantes

| Archivo                  | Descripción                                       |
|--------------------------|---------------------------------------------------|
| `weights_final.txt`      | Pesos entrenados para cada neurona                |
| `bmu_mapping.txt`        | Asignación de entradas a neuronas (output mapper) |
| `train_som`              | Binario para entrenamiento                        |
| `test_mapper`            | Binario para mapeo                                |
| `visualize_som`          | Binario con visualización OpenGL                  |

---

##  Conceptos Clave

- **SOM (Self-Organizing Map)**: Red neuronal no supervisada que proyecta datos de alta dimensión a una representación de baja dimensión (en este caso, 3D).
- **BMU (Best Matching Unit)**: Neurona cuyos pesos están más cercanos al vector de entrada.
- **OpenGL**: Biblioteca gráfica usada para representar visualmente la red neuronal.

---

##  RESULTADOS:

![image](https://github.com/user-attachments/assets/c4474935-1707-453b-aba0-90c80a52af1e)

![image](https://github.com/user-attachments/assets/6617aed0-ab80-4899-8f27-a5fe0045b09a)

![image](https://github.com/user-attachments/assets/7c669b07-a598-456d-b3da-e440a49c3b4e)

![image](https://github.com/user-attachments/assets/8e4e5508-ba07-4524-b804-d2e71200ef68)

![image](https://github.com/user-attachments/assets/21927ecd-59f3-4ddf-8b8b-4940bfa48c35)

![image](https://github.com/user-attachments/assets/69e4c5da-93ff-4da7-90c1-5d7cdd435987)

---

##  Posibles Mejoras

- Añadir opciones interactivas en la visualización (rotación libre, zoom, etiquetas).
- Integración con datasets reales como imágenes directamente.
- Exportar métricas de entrenamiento y calidad del mapeo.

---

##  Aplicaciones Futuras

- Exploración de datos visuales o genómicos en 3D.
- Reducción de dimensionalidad para conjuntos de datos complejos.
- Visualización educativa para cursos de redes neuronales.

---


## Comentarios

Si tienes preguntas sobre el funcionamiento, entrenamiento o visualización del SOM 3D, puedes abrir un issue o contactar con el autor del proyecto.
