cmake_minimum_required(VERSION 3.10)
project(SOM3D_Fashion)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

#add_executable(test_som utils/test_neuron_finder.cpp src/som.cpp)
add_executable(train_som src/train_som.cpp src/som.cpp)

add_executable(visualize_som src/visualize_som.cpp src/glad.c src/renderer.cpp src/som.cpp)

add_executable(test_mapper src/test_mapper.cpp src/som.cpp)

add_executable(summary_report src/summary_report.cpp)

target_link_libraries(visualize_som glfw GL)



