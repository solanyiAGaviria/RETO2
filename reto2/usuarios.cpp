#include "Usuarios.h"
#include <sstream>
#include <iostream>

Usuarios::Usuarios() {
    cedula = "";
    clave = "";
    calificacion = 0.0f;
}

Usuarios::Usuarios(const std::string& ced, const std::string& clv, float calif) {
    cedula = ced;
    clave = clv;
    calificacion = calif;
}

Usuarios* Usuarios::desdeLinea(const std::string& linea) {
    std::stringstream ss(linea);
    std::string ced, clv, califStr;
    float calif;

    std::getline(ss, ced, ';');
    std::getline(ss, clv, ';');
    std::getline(ss, califStr, ';');

    calif = std::stof(califStr);

    return new Usuarios(ced, clv, calif);
}

void Usuarios::mostrar() const {
    std::cout << "Cédula: " << cedula
              << " | Clave: " << clave
              << " | Calificación: " << calificacion << std::endl;
}
