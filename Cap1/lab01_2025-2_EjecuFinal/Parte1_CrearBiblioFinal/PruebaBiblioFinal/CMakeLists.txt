cmake_minimum_required(VERSION 4.2)
project(PruebaBiblioFinal)

set(CMAKE_CXX_STANDARD 20)

add_executable(PruebaBiblioFinal main.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_CURRENT_SOURCE_DIR}/MisBibliotecas")

target_link_libraries(PruebaBiblioFinal PRIVATE Libreria)