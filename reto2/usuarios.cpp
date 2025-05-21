#include "usuarios.h"
#include <cstring>
#include<iostream>

usuarios() {}

usuarios::usuarios(const char* doc, const char* pass, int tiempo, float punt) {
    strcpy(documento, doc);
    strcpy(clave, pass);
    tiempoplat = tiempo;
    puntuacion = punt;
}

void mostrarDatos() {
    std::cout << "Usuario: " << documento << ", Tiempo: " << tiempoplat << ", Puntuación: " << puntuacion << std::endl;
}

