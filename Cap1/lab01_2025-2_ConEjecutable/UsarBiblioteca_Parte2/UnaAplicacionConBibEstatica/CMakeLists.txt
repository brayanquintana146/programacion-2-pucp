cmake_minimum_required(VERSION 4.2)
project(UnaAplicacionConBibEstatica)

set(CMAKE_CXX_STANDARD 20)

add_executable(UnaAplicacionConBibEstatica main.cpp
        funcionesAux.cpp
        funcionesAux.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_CURRENT_SOURCE_DIR}/MisBibliotecas")

target_link_libraries(UnaAplicacionConBibEstatica PRIVATE Libreria Libreria2 Libreria3)