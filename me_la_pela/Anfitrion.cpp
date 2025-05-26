// Anfitrion.cpp
#include "Anfitrion.h"
#include <iostream>

Anfitrion::Anfitrion() : cedula(0), antiguedad_meses(0), calificacion(0.0f), cantidadAlojamientos(0) {
    alojamientos = new Alojamiento*[MAX_ALOJAMIENTOS];
    for (int i = 0; i < MAX_ALOJAMIENTOS; i++) alojamientos[i] = nullptr;
}

Anfitrion::Anfitrion(long ced, const std::string& nom, const std::string& clave_, int ant, float calif)
    : cedula(ced), nombre(nom), clave(clave_), antiguedad_meses(ant), calificacion(calif), cantidadAlojamientos(0) {
    alojamientos = new Alojamiento*[MAX_ALOJAMIENTOS];
    for (int i = 0; i < MAX_ALOJAMIENTOS; i++) alojamientos[i] = nullptr;
}

Anfitrion::Anfitrion(const Anfitrion &otro) {
    cedula = otro.cedula;
    nombre = otro.nombre;
    clave = otro.clave;
    antiguedad_meses = otro.antiguedad_meses;
    calificacion = otro.calificacion;
    cantidadAlojamientos = otro.cantidadAlojamientos;
    alojamientos = new Alojamiento*[MAX_ALOJAMIENTOS];
    for (int i = 0; i < MAX_ALOJAMIENTOS; i++) alojamientos[i] = otro.alojamientos[i];
}

Anfitrion::~Anfitrion() {
    delete[] alojamientos;
}

long Anfitrion::getCedula() const { return cedula; }
std::string Anfitrion::getNombre() const { return nombre; }
std::string Anfitrion::getClave() const { return clave; }
int Anfitrion::getAntiguedad() const { return antiguedad_meses; }
float Anfitrion::getCalificacion() const { return calificacion; }
int Anfitrion::getCantidadAlojamientos() const { return cantidadAlojamientos; }
Alojamiento** Anfitrion::getAlojamientos() { return alojamientos; }

void Anfitrion::setCedula(long c) { cedula = c; }
void Anfitrion::setNombre(const std::string& n) { nombre = n; }
void Anfitrion::setClave(const std::string& c) { clave = c; }
void Anfitrion::setAntiguedad(int a) { antiguedad_meses = a; }
void Anfitrion::setCalificacion(float cal) { calificacion = cal; }

Anfitrion& Anfitrion::operator=(const Anfitrion &otro) {
    if (this != &otro) {
        cedula = otro.cedula;
        nombre = otro.nombre;
        clave = otro.clave;
        antiguedad_meses = otro.antiguedad_meses;
        calificacion = otro.calificacion;
        cantidadAlojamientos = otro.cantidadAlojamientos;
        for (int i = 0; i < MAX_ALOJAMIENTOS; i++) alojamientos[i] = otro.alojamientos[i];
    }
    return *this;
}

void Anfitrion::añadirAlojamiento(Alojamiento* a) {
    if (cantidadAlojamientos < MAX_ALOJAMIENTOS) {
        alojamientos[cantidadAlojamientos++] = a;
    }
}

void Anfitrion::mostrarAnfitrion() const {
    std::cout << "Nombre: " << nombre
              << " | Antigüedad: " << antiguedad_meses << " meses"
              << " | Calificación: " << calificacion << std::endl;
}

void Anfitrion::mostrarCaracteristicas() const {
    std::cout << "Cédula: " << cedula
              << "\nNombre: " << nombre
              << "\nAntigüedad: " << antiguedad_meses << " meses"
              << "\nCalificación: " << calificacion << std::endl;
}

Alojamiento* Anfitrion::getAlojamiento(int index) const {
    if (index >= 0 && index < cantidadAlojamientos) {
        return alojamientos[index];
    }
    return nullptr;
}
