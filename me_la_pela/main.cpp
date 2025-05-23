// main.cpp
#include <iostream>
#include "CargaDatos.h"

using namespace std;

int main() {
    CargaDatos sistema;

    sistema.cargarAlojamientos("alojamientos.txt");
    sistema.cargarAnfitriones("anfitriones.txt");
    sistema.cargarUsuarios("usuarios.txt");
    sistema.cargarReservaciones("reservas.txt");

    cout << "\n--- Alojamientos cargados ---\n";
    for (int i = 0; i < sistema.getTotalAlojamientos(); ++i) {
        sistema.getAlojamientos()[i]->mostrarAlojamiento();
        cout << endl;
    }

    cout << "\n--- Anfitriones cargados ---\n";
    for (int i = 0; i < sistema.getTotalAnfitriones(); ++i) {
        sistema.getAnfitriones()[i]->mostrarCaracteristicas();
        cout << endl;
    }

    cout << "\n--- Usuarios cargados ---\n";
    for (int i = 0; i < sistema.getTotalUsuarios(); ++i) {
        sistema.getUsuarios()[i]->mostrarUsuario();
        sistema.getUsuarios()[i]->mostrarReservas();
        cout << endl;
    }

    cout << "\n--- Reservaciones cargadas ---\n";
    for (int i = 0; i < sistema.getTotalReservas(); ++i) {
        sistema.getReservas()[i]->mostrarComprobante();
    }

    return 0;
}
