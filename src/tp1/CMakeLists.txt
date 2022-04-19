# CMakeList.txt: proyecto de CMake para tp1, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)

# Agregue un origen al ejecutable de este proyecto.
add_executable (tp1 "tp1.cpp" "tp1.h" "ej1/ej1.h" "ej1/ej1.cpp" "ej3/ej3.cpp" "ej3/ej3.h" "ej4/ej4.cpp" "ej4/ej4.h" "ej2/ej2.cpp" "ej2/ej2.h")

# TODO: Agregue pruebas y destinos de instalación si es necesario.
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")
