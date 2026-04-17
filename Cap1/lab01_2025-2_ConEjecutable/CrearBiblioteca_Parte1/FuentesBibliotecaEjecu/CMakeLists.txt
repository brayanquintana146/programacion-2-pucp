cmake_minimum_required(VERSION 4.2)
project(FuentesBibliotecaEjecu)

set(CMAKE_CXX_STANDARD 20)

add_library(Libreria STATIC MisBibliotecas/funciones.cpp)

add_executable(FuentesBibliotecaEjecu main.cpp)

target_link_libraries(FuentesBibliotecaEjecu Libreria)