#include "Anfitrion.h"
#include <iostream>

using namespace std;

Anfitrion::Anfitrion() : cedula(0), antiguedad_meses(0), calificacion(0.0f), cantidadAlojamientos(0) {
    capacidadAlojamientos = 5;
    alojamientos = new Alojamiento*[capacidadAlojamientos];
    for (int i = 0; i < capacidadAlojamientos; i++) alojamientos[i] = nullptr;
}

Anfitrion::Anfitrion(long ced, const std::string& nom, const std::string& clave_, int ant, float calif)
    : cedula(ced), nombre(nom), clave(clave_), antiguedad_meses(ant), calificacion(calif), cantidadAlojamientos(0) {
    capacidadAlojamientos = 5;
    alojamientos = new Alojamiento*[capacidadAlojamientos];
    for (int i = 0; i < capacidadAlojamientos; i++) alojamientos[i] = nullptr;
}

Anfitrion::Anfitrion(const Anfitrion &otro) {
    cedula = otro.cedula;
    nombre = otro.nombre;
    clave = otro.clave;
    antiguedad_meses = otro.antiguedad_meses;
    calificacion = otro.calificacion;
    cantidadAlojamientos = otro.cantidadAlojamientos;
    capacidadAlojamientos = otro.capacidadAlojamientos;

    alojamientos = new Alojamiento*[capacidadAlojamientos];
    for (int i = 0; i < cantidadAlojamientos; i++) {
        alojamientos[i] = otro.alojamientos[i];
    }
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
        delete[] alojamientos;

        cedula = otro.cedula;
        nombre = otro.nombre;
        clave = otro.clave;
        antiguedad_meses = otro.antiguedad_meses;
        calificacion = otro.calificacion;
        cantidadAlojamientos = otro.cantidadAlojamientos;
        capacidadAlojamientos = otro.capacidadAlojamientos;

        alojamientos = new Alojamiento*[capacidadAlojamientos];
        for (int i = 0; i < cantidadAlojamientos; i++) {
            alojamientos[i] = otro.alojamientos[i];
        }
    }
    return *this;
}

void Anfitrion::redimensionarAlojamientos() {
    capacidadAlojamientos *= 2;
    Alojamiento** nuevo = new Alojamiento*[capacidadAlojamientos];
    for (int i = 0; i < cantidadAlojamientos; i++) {
        nuevo[i] = alojamientos[i];
    }
    delete[] alojamientos;
    alojamientos = nuevo;
}

void Anfitrion::añadirAlojamiento(Alojamiento* a) {
    if (cantidadAlojamientos >= capacidadAlojamientos)
        redimensionarAlojamientos();

    alojamientos[cantidadAlojamientos++] = a;
}

void Anfitrion::mostrarAnfitrion() const {
    std::cout << "Nombre: " << nombre
              << " \n| Antiguedad: " << antiguedad_meses << " meses"
              << " \n| Calificacion: " << calificacion << std::endl;
}

void Anfitrion::mostrarCaracteristicas() const {
    std::cout << "Cedula: " << cedula
              << "\nNombre: " << nombre
              << "\nAntiguedad: " << antiguedad_meses << " meses"
              << "\nCalificacion: " << calificacion << "\n\n";
}

Alojamiento* Anfitrion::getAlojamiento(int index) const {
    if (index >= 0 && index < cantidadAlojamientos) {
        return alojamientos[index];
    }
    return nullptr;
}
