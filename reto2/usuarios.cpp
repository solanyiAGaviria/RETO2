#include "Usuarios.h"
#include <iostream>

Usuarios::Usuarios() {}

Usuarios::Usuarios(const std::string& nom, const std::string& doc, const std::string& clv,
                 const std::string& tiempo, const std::string& punt, const std::string& ident) {
    nombre = nom;
    documento = doc;
    clave = clv;
    tiempoPlataforma = tiempo;
    puntuacion = punt;
    id = ident;
}

void Usuarios::mostrar() const {
    std::cout << "Nombre: " << nombre << "\n";
    std::cout << "Documento: " << documento << "\n";
    std::cout << "Clave: " << clave << "\n";
    std::cout << "Tiempo Plataforma: " << tiempoPlataforma << "\n";
    std::cout << "Puntuación: " << puntuacion << "\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "-------------------------\n";
}
