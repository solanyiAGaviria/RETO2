#include "Alojamiento.h"
#include "Anfitrion.h"
#include <iostream>

using namespace std;

Alojamiento::Alojamiento() : id(0), precio_noche(0), anfitrion(nullptr), cantidadReservas(0) {
    capacidadReservas = 5;
    reservas = new Reservacion*[capacidadReservas];
    for (int i = 0; i < capacidadReservas; i++) reservas[i] = nullptr;
}

Alojamiento::Alojamiento(int id_, const string& nombre_, const string& dep, const string& mun,
                         const string& tipo_, const string& dir, int precio, const string& amen)
    : id(id_), nombre(nombre_), departamento(dep), municipio(mun),
    tipo(tipo_), direccion(dir), precio_noche(precio), amenidades(amen),
    anfitrion(nullptr), cantidadReservas(0) {
    capacidadReservas = 5;
    reservas = new Reservacion*[capacidadReservas];
    for (int i = 0; i < capacidadReservas; i++) reservas[i] = nullptr;
}

Alojamiento::Alojamiento(const Alojamiento& otro) {
    id = otro.id;
    nombre = otro.nombre;
    departamento = otro.departamento;
    municipio = otro.municipio;
    tipo = otro.tipo;
    direccion = otro.direccion;
    precio_noche = otro.precio_noche;
    amenidades = otro.amenidades;
    anfitrion = otro.anfitrion;

    cantidadReservas = otro.cantidadReservas;
    capacidadReservas = otro.capacidadReservas;
    reservas = new Reservacion*[capacidadReservas];
    for (int i = 0; i < cantidadReservas; i++) {
        reservas[i] = otro.reservas[i];
    }
}

Alojamiento::~Alojamiento() {
    delete[] reservas;
}

void Alojamiento::redimensionarReservas() {
    capacidadReservas *= 2;
    Reservacion** nuevo = new Reservacion*[capacidadReservas];
    for (int i = 0; i < cantidadReservas; i++) {
        nuevo[i] = reservas[i];
    }
    delete[] reservas;
    reservas = nuevo;
}

int Alojamiento::getId() const { return id; }
string Alojamiento::getNombre() const { return nombre; }
string Alojamiento::getDepartamento() const { return departamento; }
string Alojamiento::getMunicipio() const { return municipio; }
string Alojamiento::getTipo() const { return tipo; }
string Alojamiento::getDireccion() const { return direccion; }
int Alojamiento::getPrecioNoche() const { return precio_noche; }
string Alojamiento::getAmenidades() const { return amenidades; }
Anfitrion* Alojamiento::getAnfitrion() const { return anfitrion; }
int Alojamiento::getCantidadReservas() const { return cantidadReservas; }
Reservacion** Alojamiento::getReservas() { return reservas; }

Reservacion* Alojamiento::getReserva(int index) const {
    if (index >= 0 && index < cantidadReservas)
        return reservas[index];
    return nullptr;
}

void Alojamiento::setAnfitrion(Anfitrion* a) { anfitrion = a; }
void Alojamiento::setPrecioNoche(int p) { precio_noche = p; }

void Alojamiento::añadirReserva(Reservacion* r) {
    if (cantidadReservas >= capacidadReservas)
        redimensionarReservas();
    reservas[cantidadReservas++] = r;
}

void Alojamiento::quitarReserva(const string& codigo) {
    for (int i = 0; i < cantidadReservas; i++) {
        if (reservas[i] && reservas[i]->getCodigo() == codigo) {
            reservas[i] = nullptr;
            break;
        }
    }
}

void Alojamiento::resetReservas() {
    for (int i = 0; i < cantidadReservas; i++) {
        reservas[i] = nullptr;
    }
    cantidadReservas = 0;
}

void Alojamiento::mostrarAlojamiento() const {
    cout << "\n--- Alojamiento ---\n";
    cout << "ID: " << id
         << "\nNombre: " << nombre
         << "\nDepartamento: " << departamento
         << "\nMunicipio: " << municipio
         << "\nTipo: " << tipo
         << "\nDireccion: " << direccion
         << "\nPrecio por noche: " << precio_noche
         << "\nAmenidades: " << amenidades << endl;

    if (anfitrion) {
        cout << "Anfitrion: " << anfitrion->getNombre()
        << " | Antiguedad: " << anfitrion->getAntiguedad()
        << " meses | Calificacion: " << anfitrion->getCalificacion() << endl;
    } else {
        cout << "Anfitrion: No asignado.\n";
    }
}

void Alojamiento::misReservas() const {
    cout << "\n--- Reservas del Alojamiento " << id << " ---\n";
    for (int i = 0; i < cantidadReservas; i++) {
        if (reservas[i] && !reservas[i]->esGenerica()) {
            cout << "Reserva: " << reservas[i]->getCodigo()
            << " | Desde: "; reservas[i]->getFechaInicio().mostrarDiaMes();
            cout << " | Hasta: "; reservas[i]->getFechaFin().mostrarDiaMes();
            cout << endl;
        }
    }
}

bool Alojamiento::estaDisponible(const Fecha& f, const Fecha& hoy) const {
    if (f < hoy) return false;
    for (int i = 0; i < cantidadReservas; i++) {
        if (reservas[i] && !reservas[i]->esGenerica()) {
            Fecha inicio = reservas[i]->getFechaInicio();
            Fecha fin = reservas[i]->getFechaFin();
            if (f >= inicio && f <= fin)
                return false;
        }
    }
    return true;
}

void Alojamiento::fechasDisponibles(const Fecha& desde) const {
    cout << "\n--- Fechas disponibles ---\n";
    Fecha inicio = desde;
    Fecha fin = inicio.sumarDias(365);
    Fecha actual = inicio;

    while (actual <= fin) {
        // Buscar el primer día disponible
        while (actual <= fin && !estaDisponible(actual, desde)) {
            actual = actual.sumarDias(1);
        }

        if (actual > fin) break;

        Fecha bloqueInicio = actual;

        // Buscar fin del bloque disponible
        while (actual <= fin && estaDisponible(actual, desde)) {
            actual = actual.sumarDias(1);
        }

        Fecha bloqueFin = actual.sumarDias(-1);
        cout << "Disponible del ";
        bloqueInicio.mostrarDiaMes();
        cout << " al ";
        bloqueFin.mostrarDiaMes();
        cout << "\n";
    }
}

Alojamiento& Alojamiento::operator=(const Alojamiento& otro) {
    if (this != &otro) {
        delete[] reservas;

        id = otro.id;
        nombre = otro.nombre;
        departamento = otro.departamento;
        municipio = otro.municipio;
        tipo = otro.tipo;
        direccion = otro.direccion;
        precio_noche = otro.precio_noche;
        amenidades = otro.amenidades;
        anfitrion = otro.anfitrion;
        cantidadReservas = otro.cantidadReservas;
        capacidadReservas = otro.capacidadReservas;

        reservas = new Reservacion*[capacidadReservas];
        for (int i = 0; i < cantidadReservas; i++) {
            reservas[i] = otro.reservas[i];
        }
    }
    return *this;
}
