// Alojamiento.cpp
#include "Alojamiento.h"
#include "Anfitrion.h"
#include <iostream>

#define MAX_RESERVAS 100

Alojamiento::Alojamiento() : id_alojamiento(0), precio_noche(0), anfitrion(nullptr), cantidadReservas(0) {
    reservas = new Reservacion*[MAX_RESERVAS];
    for (int i = 0; i < MAX_RESERVAS; i++) reservas[i] = nullptr;
}

Alojamiento::Alojamiento(int id, const std::string& nom, const std::string& dep, const std::string& mun, const std::string& tipo_,
                         const std::string& dir, int precio, const std::string& amenidades_)
    : id_alojamiento(id), nombre(nom), departamento(dep), municipio(mun), tipo(tipo_), direccion(dir),
    precio_noche(precio), amenidades(amenidades_), anfitrion(nullptr), cantidadReservas(0) {
    reservas = new Reservacion*[MAX_RESERVAS];
    for (int i = 0; i < MAX_RESERVAS; i++) reservas[i] = nullptr;
}

Alojamiento::Alojamiento(const Alojamiento &otro) {
    id_alojamiento = otro.id_alojamiento;
    nombre = otro.nombre;
    departamento = otro.departamento;
    municipio = otro.municipio;
    tipo = otro.tipo;
    direccion = otro.direccion;
    precio_noche = otro.precio_noche;
    amenidades = otro.amenidades;
    anfitrion = otro.anfitrion;
    cantidadReservas = otro.cantidadReservas;

    reservas = new Reservacion*[MAX_RESERVAS];
    for (int i = 0; i < MAX_RESERVAS; i++)
        reservas[i] = otro.reservas[i];
}

Alojamiento::~Alojamiento() {
    delete[] reservas;
}

int Alojamiento::getId() const { return id_alojamiento; }
std::string Alojamiento::getNombre() const { return nombre; }
std::string Alojamiento::getDepartamento() const { return departamento; }
std::string Alojamiento::getMunicipio() const { return municipio; }
std::string Alojamiento::getTipo() const { return tipo; }
std::string Alojamiento::getDireccion() const { return direccion; }
int Alojamiento::getPrecioNoche() const { return precio_noche; }
std::string Alojamiento::getAmenidades() const { return amenidades; }

void Alojamiento::setId(int id) { id_alojamiento = id; }
void Alojamiento::setNombre(const std::string& nom) { nombre = nom; }
void Alojamiento::setDepartamento(const std::string& dep) { departamento = dep; }
void Alojamiento::setMunicipio(const std::string& mun) { municipio = mun; }
void Alojamiento::setTipo(const std::string& t) { tipo = t; }
void Alojamiento::setDireccion(const std::string& dir) { direccion = dir; }
void Alojamiento::setPrecioNoche(int precio) { precio_noche = precio; }
void Alojamiento::setAmenidades(const std::string& amen) { amenidades = amen; }

void Alojamiento::setAnfitrion(Anfitrion* a) { anfitrion = a; }
Anfitrion* Alojamiento::getAnfitrion() const { return anfitrion; }

Alojamiento& Alojamiento::operator=(const Alojamiento &otro) {
    if (this != &otro) {
        id_alojamiento = otro.id_alojamiento;
        nombre = otro.nombre;
        departamento = otro.departamento;
        municipio = otro.municipio;
        tipo = otro.tipo;
        direccion = otro.direccion;
        precio_noche = otro.precio_noche;
        amenidades = otro.amenidades;
        anfitrion = otro.anfitrion;
        cantidadReservas = otro.cantidadReservas;

        for (int i = 0; i < MAX_RESERVAS; i++)
            reservas[i] = otro.reservas[i];
    }
    return *this;
}

void Alojamiento::añadirReserva(Reservacion* r) {
    if (cantidadReservas < MAX_RESERVAS) {
        reservas[cantidadReservas++] = r;
    }
}

void Alojamiento::quitarReserva(const std::string& codigoReserva) {
    for (int i = 0; i < cantidadReservas; i++) {
        if (reservas[i] && reservas[i]->getCodigo() == codigoReserva) {
            reservas[i] = nullptr;
            break;
        }
    }
}

void Alojamiento::mostrarAlojamiento() const {
    std::cout << "ID: " << id_alojamiento << "\nNombre: " << nombre
              << "\nDepartamento: " << departamento << "\nMunicipio: " << municipio
              << "\nTipo: " << tipo << "\nDireccion: " << direccion
              << "\nPrecio por noche: " << precio_noche << "\nAmenidades: " << amenidades;
    if (anfitrion) {
        std::cout << "\nAnfitrión: " << anfitrion->getNombre()
                  << ", Antigüedad: " << anfitrion->getAntiguedad()
                  << " meses, Calificación: " << anfitrion->getCalificacion();
    }
    std::cout << "\n";
}

void Alojamiento::misReservas() const {
    for (int i = 0; i < cantidadReservas; i++) {
        if (reservas[i]) {
            std::cout << "Reserva: " << reservas[i]->getCodigo() << " | ";
            reservas[i]->getFechaInicio().mostrarDiaMes();
            std::cout << " - ";
            reservas[i]->getFechaFin().mostrarDiaMes();
            std::cout << "\n";
        }
    }
}

void Alojamiento::fechasDisponibles(const Fecha& hoy) const {
    Fecha inicio = hoy;
    Fecha finLimite = hoy.sumarDias(364);
    const int maxDias = 365;
    bool ocupado[maxDias] = {false};

    // Marcar días ocupados por reservas
    for (int i = 0; i < cantidadReservas; i++) {
        if (reservas[i] && !reservas[i]->esGenerica()) {
            Fecha ini = reservas[i]->getFechaInicio();
            Fecha fin = reservas[i]->getFechaFin();
            for (int d = 0; d < maxDias; d++) {
                Fecha dia = hoy.sumarDias(d);
                if (dia >= ini && dia <= fin)
                    ocupado[d] = true;
            }
        }
    }

    // Encabezado
    std::cout << "\n--- Fechas disponibles ---" << std::endl;
    std::cout << "Desde ";
    inicio.mostrarDiaMes();  // esta imprime con endl
    std::cout << "Hasta ";
    finLimite.mostrarDiaMes();

    // Mostrar rangos disponibles
    bool enBloque = false;
    Fecha inicioBloque;

    for (int i = 0; i < maxDias; i++) {
        if (!ocupado[i]) {
            if (!enBloque) {
                enBloque = true;
                inicioBloque = hoy.sumarDias(i);
            }
        } else {
            if (enBloque) {
                Fecha finBloque = hoy.sumarDias(i - 1);
                std::cout << "\nDisponible del ";
                inicioBloque.mostrarDiaMes();
                std::cout << "al ";
                finBloque.mostrarDiaMes();
                enBloque = false;
            }
        }
    }

    // Finaliza último bloque si termina libre
    if (enBloque) {
        Fecha finBloque = hoy.sumarDias(maxDias - 1);
        std::cout << "\nDisponible del ";
        inicioBloque.mostrarDiaMes();
        std::cout << "al ";
        finBloque.mostrarDiaMes();
    }
}

bool Alojamiento::estaDisponible(const Fecha& f, const Fecha& hoy) const {
    // Fuera de rango de fechas futuras
    if (f < hoy || f > hoy.sumarDias(364)) return false;

    // Revisa si está ocupada por una reserva
    for (int i = 0; i < cantidadReservas; i++) {
        if (reservas[i] && !reservas[i]->esGenerica()) {
            Fecha ini = reservas[i]->getFechaInicio();
            Fecha fin = reservas[i]->getFechaFin();
            if (f >= ini && f <= fin)
                return false;
        }
    }
    return true;
}


Reservacion** Alojamiento::getReservas() {
    return reservas;
}

int Alojamiento::getCantidadReservas() const {
    return cantidadReservas;
}
