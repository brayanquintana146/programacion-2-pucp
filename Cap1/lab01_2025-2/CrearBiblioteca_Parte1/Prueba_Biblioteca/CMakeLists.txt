cmake_minimum_required(VERSION 4.2)
project(Prueba_Biblioteca)

set(CMAKE_CXX_STANDARD 20)

add_executable(Prueba_Biblioteca main.cpp)

target_link_libraries(Prueba_Biblioteca ${CMAKE_SOURCE_DIR}/libFuentes__Bibioteca_2025_2.a)
