#include "Usuario.h"
#include <iostream>

using namespace std;

Usuario::Usuario() : cedula(0), calificacion(0.0f), cantidadReservas(0) {
    capacidadReservas = 5;
    reservas = new Reservacion*[capacidadReservas];
    for (int i = 0; i < capacidadReservas; i++) reservas[i] = nullptr;
}

Usuario::Usuario(int ced, const string& nom, const string& clave_, float calif)
    : cedula(ced), nombre(nom), clave(clave_), calificacion(calif), cantidadReservas(0) {
    capacidadReservas = 5;
    reservas = new Reservacion*[capacidadReservas];
    for (int i = 0; i < capacidadReservas; i++) reservas[i] = nullptr;
}

Usuario::Usuario(const Usuario& otro) {
    cedula = otro.cedula;
    nombre = otro.nombre;
    clave = otro.clave;
    calificacion = otro.calificacion;
    cantidadReservas = otro.cantidadReservas;
    capacidadReservas = otro.capacidadReservas;

    reservas = new Reservacion*[capacidadReservas];
    for (int i = 0; i < cantidadReservas; i++) {
        reservas[i] = otro.reservas[i];
    }
}

Usuario::~Usuario() {
    delete[] reservas;
}

void Usuario::redimensionarReservas() {
    capacidadReservas *= 2;
    Reservacion** nuevo = new Reservacion*[capacidadReservas];
    for (int i = 0; i < cantidadReservas; i++) {
        nuevo[i] = reservas[i];
    }
    delete[] reservas;
    reservas = nuevo;
}

void Usuario::añadirReserva(Reservacion* r) {
    if (cantidadReservas >= capacidadReservas)
        redimensionarReservas();
    reservas[cantidadReservas++] = r;
}

void Usuario::quitarReserva(const string& codigo) {
    for (int i = 0; i < cantidadReservas; i++) {
        if (reservas[i] && reservas[i]->getCodigo() == codigo) {
            reservas[i] = nullptr;
            break;
        }
    }
}

void Usuario::resetReservas() {
    for (int i = 0; i < cantidadReservas; i++) {
        reservas[i] = nullptr;
    }
    cantidadReservas = 0;
}

int Usuario::getCedula() const { return cedula; }
string Usuario::getNombre() const { return nombre; }
string Usuario::getClave() const { return clave; }
float Usuario::getCalificacion() const { return calificacion; }
int Usuario::getCantidadReservas() const { return cantidadReservas; }
Reservacion** Usuario::getReservas() { return reservas; }

Reservacion* Usuario::getReserva(int index) const {
    if (index >= 0 && index < cantidadReservas)
        return reservas[index];
    return nullptr;
}

void Usuario::setCedula(long c) { cedula = c; }
void Usuario::setNombre(const string& n) { nombre = n; }
void Usuario::setClave(const string& c) { clave = c; }
void Usuario::setCalificacion(float cal) { calificacion = cal; }

void Usuario::mostrarUsuario() const {
    cout << "Usuario: " << nombre << "\nCalificacion: " << calificacion << endl;
}

void Usuario::mostrarReservas() const {
    for (int i = 0; i < cantidadReservas; i++) {
        if (reservas[i] && !reservas[i]->esGenerica()) {
            cout << "Codigo: " << reservas[i]->getCodigo()
            << " | ID Alojamiento: " << reservas[i]->getIdAlojamiento()
            << " | Desde: "; reservas[i]->getFechaInicio().mostrarDiaMes();
            cout << " | Hasta: "; reservas[i]->getFechaFin().mostrarDiaMes();
            cout << endl;
        }
    }
}

Usuario& Usuario::operator=(const Usuario& otro) {
    if (this != &otro) {
        delete[] reservas;

        cedula = otro.cedula;
        nombre = otro.nombre;
        clave = otro.clave;
        calificacion = otro.calificacion;
        cantidadReservas = otro.cantidadReservas;
        capacidadReservas = otro.capacidadReservas;

        reservas = new Reservacion*[capacidadReservas];
        for (int i = 0; i < cantidadReservas; i++) {
            reservas[i] = otro.reservas[i];
        }
    }
    return *this;
}
