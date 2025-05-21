#include "anfitrion.h"
#include <cstring>
#include <iostream>

anfitrion::anfitrion() {}

anfitrion(const char* doc, int ant, float punt) {
    strcpy(documento, doc);
    antiguedad = ant;
    puntuacion = punt;
}
void mostrarDatos() {
    std::cout << "Anfitrión: " << documento << ", Antigüedad: " << antiguedad << ", Puntuación: " << puntuacion << std::endl;
}
