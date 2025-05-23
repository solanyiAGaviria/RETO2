// Usuario.cpp
#include "Usuario.h"
#include <iostream>

Usuario::Usuario() : cedula(0), calificacion(0.0f), cantidadReservas(0) {
    reservas = new Reservacion*[MAX_RESERVAS_USUARIO];
    for (int i = 0; i < MAX_RESERVAS_USUARIO; i++) reservas[i] = nullptr;
}

Usuario::Usuario(long ced, const std::string& nom, const std::string& clave_, float calif)
    : cedula(ced), nombre(nom), clave(clave_), calificacion(calif), cantidadReservas(0) {
    reservas = new Reservacion*[MAX_RESERVAS_USUARIO];
    for (int i = 0; i < MAX_RESERVAS_USUARIO; i++) reservas[i] = nullptr;
}

Usuario::Usuario(const Usuario &otro) {
    cedula = otro.cedula;
    nombre = otro.nombre;
    clave = otro.clave;
    calificacion = otro.calificacion;
    cantidadReservas = otro.cantidadReservas;
    reservas = new Reservacion*[MAX_RESERVAS_USUARIO];
    for (int i = 0; i < MAX_RESERVAS_USUARIO; i++) reservas[i] = otro.reservas[i];
}

Usuario::~Usuario() {
    delete[] reservas;
}

long Usuario::getCedula() const { return cedula; }
std::string Usuario::getNombre() const { return nombre; }
std::string Usuario::getClave() const { return clave; }
float Usuario::getCalificacion() const { return calificacion; }
Reservacion** Usuario::getReservas() { return reservas; }
int Usuario::getCantidadReservas() const { return cantidadReservas; }

void Usuario::setCedula(long c) { cedula = c; }
void Usuario::setNombre(const std::string& n) { nombre = n; }
void Usuario::setClave(const std::string& c) { clave = c; }
void Usuario::setCalificacion(float cal) { calificacion = cal; }

Usuario& Usuario::operator=(const Usuario &otro) {
    if (this != &otro) {
        cedula = otro.cedula;
        nombre = otro.nombre;
        clave = otro.clave;
        calificacion = otro.calificacion;
        cantidadReservas = otro.cantidadReservas;
        for (int i = 0; i < MAX_RESERVAS_USUARIO; i++) reservas[i] = otro.reservas[i];
    }
    return *this;
}

void Usuario::añadirReserva(Reservacion* r) {
    if (cantidadReservas < MAX_RESERVAS_USUARIO) {
        reservas[cantidadReservas++] = r;
    }

}

void Usuario::quitarReserva(const std::string& codigoReserva) {
    for (int i = 0; i < cantidadReservas; i++) {
        if (reservas[i] && reservas[i]->getCodigo() == codigoReserva) {
            reservas[i] = nullptr;
            break;
        }
    }
}

void Usuario::mostrarReservas() const {
    std::cout << "\nReservas del usuario " << nombre << ":\n";
    for (int i = 0; i < cantidadReservas; i++) {
        if (reservas[i]) {
            std::cout << "Reserva: " << reservas[i]->getCodigo()
            << " | Alojamiento: " << reservas[i]->getIdAlojamiento()
            << " | Inicio: ";
            reservas[i]->getFechaInicio().mostrarDiaMes();
            std::cout << " | Fin: ";
            reservas[i]->getFechaFin().mostrarDiaMes();
            std::cout << "\n";
        }
    }
}

void Usuario::mostrarUsuario() const {
    std::cout << "Usuario: " << nombre << " | Calificación: " << calificacion << "\n";
}
