#include "anfitrion.h"
#include <iostream>

anfitrion::anfitrion() {
    cantidadAlojamientos = 0;
    alojamientos = nullptr;
}

anfitrion::anfitrion(std::string ced, std::string cla, int antig, float calif, std::string* aloj, int cant) {
    cedula = ced;
    clave = cla;
    antiguedad_meses = antig;
    calificacion = calif;
    cantidadAlojamientos = cant;

    alojamientos = new std::string[cant];
    for (int i = 0; i < cant; i++) {
        alojamientos[i] = aloj[i];
    }
}

anfitrion::~anfitrion() {
    delete[] alojamientos;
}

void anfitrion::mostrar() const {
    std::cout << "Antigüedad: " << antiguedad_meses << " meses\n";
    std::cout << "Calificación: " << calificacion << "\n";
    std::cout << "Alojamientos: ";
    for (int i = 0; i < cantidadAlojamientos; i++) {
        std::cout << alojamientos[i] << " ";
    }
    std::cout << "\n";
}
