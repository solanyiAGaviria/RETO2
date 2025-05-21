#include "alojamientos.h"
#include <cstring>
#include <iostream>

alojamientos() {}

alojamientos(const char* nom, const char* cod, const char* anfit, const char* depto, const char* muni,
             const char* tip, const char* dir, int precio, const char* amen) {
    strcpy(nombre, nom);
    strcpy(codigo, cod);
    strcpy(anfitrion, anfit);
    strcpy(departamento, depto);
    strcpy(municipio, muni);
    strcpy(tipo, tip);
    strcpy(direccion, dir);
    precioNoche = precio;
    strcpy(amenidades, amen);
}
void mostrarDatos() {
    std::cout << "Alojamiento: " << nombre << ", Precio: " << precioNoche << " COP/noche" << std::endl;
}
