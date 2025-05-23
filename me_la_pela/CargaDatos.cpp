// CargaDatos.cpp
#include "CargaDatos.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

CargaDatos::CargaDatos() {
    alojamientos = new Alojamiento*[MAX_ALOJAMIENTOS];
    anfitriones = new Anfitrion*[MAX_ANFITRIONES];
    usuarios = new Usuario*[MAX_USUARIOS];
    reservas = new Reservacion*[MAX_RESERVAS];
    totalAlojamientos = totalAnfitriones = totalUsuarios = totalReservas = 0;
}

CargaDatos::~CargaDatos() {
    delete[] alojamientos;
    delete[] anfitriones;
    delete[] usuarios;
    delete[] reservas;
}

Alojamiento** CargaDatos::getAlojamientos() { return alojamientos; }
int CargaDatos::getTotalAlojamientos() const { return totalAlojamientos; }

Anfitrion** CargaDatos::getAnfitriones() { return anfitriones; }
int CargaDatos::getTotalAnfitriones() const { return totalAnfitriones; }

Usuario** CargaDatos::getUsuarios() { return usuarios; }
int CargaDatos::getTotalUsuarios() const { return totalUsuarios; }

Reservacion** CargaDatos::getReservas() { return reservas; }
int CargaDatos::getTotalReservas() const { return totalReservas; }

void CargaDatos::cargarAlojamientos(const string& ruta) {
    ifstream file(ruta);
    if (!file.is_open()) {
        cerr << "No se pudo abrir archivo de alojamientos\n";
        return;
    }

    string linea;
    getline(file, linea);

    while (getline(file, linea)) {
        stringstream ss(linea);
        string token;

        int id, precio;
        string nombre, dep, mun, tipo, dir, amen;

        getline(ss, token, ';'); id = stoi(token);
        getline(ss, nombre, ';');
        getline(ss, dep, ';');
        getline(ss, mun, ';');
        getline(ss, tipo, ';');
        getline(ss, dir, ';');
        getline(ss, token, ';'); precio = stoi(token);
        getline(ss, amen);

        alojamientos[totalAlojamientos++] = new Alojamiento(id, nombre, dep, mun, tipo, dir, precio, amen);
    }
    file.close();
}

void CargaDatos::cargarAnfitriones(const string& ruta) {
    ifstream file(ruta);
    if (!file.is_open()) {
        cerr << "No se pudo abrir archivo de anfitriones\n";
        return;
    }

    string linea;
    getline(file, linea);

    while (getline(file, linea)) {
        stringstream ss(linea);
        string token;

        long cedula;
        string nombre, clave, alojamientos_str;
        int antiguedad;
        float calificacion;

        getline(ss, token, ';'); cedula = stol(token);
        getline(ss, nombre, ';');
        getline(ss, clave, ';');
        getline(ss, token, ';'); antiguedad = stoi(token);
        getline(ss, token, ';'); calificacion = stof(token);
        getline(ss, alojamientos_str);

        Anfitrion* anfitrion = new Anfitrion(cedula, nombre, clave, antiguedad, calificacion);

        stringstream alojamientos_ss(alojamientos_str);
        while (getline(alojamientos_ss, token, ',')) {
            int id = stoi(token);
            Alojamiento* aloja = buscarAlojamientoPorId(id);
            if (aloja) {
                aloja->setAnfitrion(anfitrion);
                anfitrion->añadirAlojamiento(aloja);
            }
        }

        anfitriones[totalAnfitriones++] = anfitrion;
    }
    file.close();
}

void CargaDatos::cargarUsuarios(const string& ruta) {
    ifstream file(ruta);
    if (!file.is_open()) {
        cerr << "No se pudo abrir archivo de usuarios\n";
        return;
    }

    string linea;
    getline(file, linea);

    while (getline(file, linea)) {
        stringstream ss(linea);
        string token;

        long cedula;
        string nombre, clave;
        float calificacion;

        getline(ss, token, ';'); cedula = stol(token);
        getline(ss, nombre, ';');
        getline(ss, clave, ';');
        getline(ss, token); calificacion = stof(token);

        usuarios[totalUsuarios++] = new Usuario(cedula, nombre, clave, calificacion);
    }
    file.close();
}

void CargaDatos::cargarReservaciones(const string& ruta) {
    ifstream file(ruta);
    if (!file.is_open()) {
        cerr << "No se pudo abrir archivo de reservaciones\n";
        return;
    }

    string linea;
    getline(file, linea);

    while (getline(file, linea)) {
        stringstream ss(linea);
        string token;

        string codigo, metodo_pago, pregunta;
        long cedula_usuario;
        int id_aloja;
        string fechaPagoStr, fechaIniStr, fechaFinStr;

        getline(ss, codigo, ';');
        getline(ss, token, ';'); cedula_usuario = stol(token);
        getline(ss, token, ';'); id_aloja = stoi(token);
        getline(ss, fechaPagoStr, ';');
        getline(ss, metodo_pago, ';');
        getline(ss, fechaIniStr, ';');
        getline(ss, fechaFinStr, ';');
        getline(ss, pregunta);

        int dp, mp, ap, di, mi, ai, df, mf, af;
        sscanf(fechaPagoStr.c_str(), "%d/%d/%d", &dp, &mp, &ap);
        sscanf(fechaIniStr.c_str(), "%d/%d/%d", &di, &mi, &ai);
        sscanf(fechaFinStr.c_str(), "%d/%d/%d", &df, &mf, &af);

        Fecha fecha_pago(dp, mp, ap);
        Fecha fecha_ini(di, mi, ai);
        Fecha fecha_fin(df, mf, af);

        Reservacion* reserva = new Reservacion(codigo, cedula_usuario, id_aloja,
                                               fecha_pago, metodo_pago, fecha_ini, fecha_fin, pregunta);

        Alojamiento* aloja = buscarAlojamientoPorId(id_aloja);
        Usuario* usuario = buscarUsuarioPorCedula(cedula_usuario);

        if (aloja && usuario) {
            aloja->añadirReserva(reserva);
            usuario->añadirReserva(reserva);
        }


        reservas[totalReservas++] = reserva;
    }
    file.close();
}

Alojamiento* CargaDatos::buscarAlojamientoPorId(int id) {
    for (int i = 0; i < totalAlojamientos; i++) {
        if (alojamientos[i]->getId() == id)
            return alojamientos[i];
    }
    return nullptr;
}

Usuario* CargaDatos::buscarUsuarioPorCedula(long cedula) {
    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i]->getCedula() == cedula)
            return usuarios[i];
    }
    return nullptr;
}
