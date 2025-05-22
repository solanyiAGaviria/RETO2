#include "alojamientos.h"
#include <sstream>
#include <iostream>

alojamiento::alojamiento() {}

alojamiento::alojamiento(string linea) {
    stringstream ss(linea);
    string campo;
    getline(ss, id, ';');
    getline(ss, nombre, ';');
    getline(ss, departamento, ';');
    getline(ss, municipio, ';');
    getline(ss, tipo, ';');
    getline(ss, direccion, ';');
    getline(ss, precio_noche, ';');
    getline(ss, amenidades);
}

void alojamiento::mostrar() const {
    cout << "ID: " << id << ", Nombre: " << nombre << ", Municipio: " << municipio << ", Precio: " << precio_noche << endl;
}
