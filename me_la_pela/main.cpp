// main.cpp
#include <iostream>
#include <string>
#include "CargaDatos.h"

using namespace std;

void menuUsuario(Usuario* usuario) {
    int opcion;
    do {
        cout << "\n--- Menú Usuario ---\n";
        cout << "1. Mostrar reservas\n";
        cout << "2. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            usuario->mostrarReservas();
            break;
        case 2:
            cout << "Saliendo del menú de usuario...\n";
            break;
        default:
            cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 2);
}

void menuAnfitrion(Anfitrion* anfitrion) {
    int opcion;
    do {
        cout << "\n--- Menú Anfitrión ---\n";
        cout << "1. Mostrar características\n";
        cout << "2. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            anfitrion->mostrarCaracteristicas();
            break;
        case 2:
            cout << "Saliendo del menú de anfitrión...\n";
            break;
        default:
            cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 2);
}

void menuPrincipal(CargaDatos& sistema) {
    string cedulaStr, clave;
    long cedula;
    int opcion;

    cout << "===== Bienvenido a UdeAStay =====\n";
    cout << "1. Iniciar sesión\n";
    cout << "2. Salir\n";
    cout << "Seleccione una opción: ";
    cin >> opcion;

    if (opcion == 2) return;

    try {
        cout << "Ingrese su cédula: ";
        cin >> cedulaStr;
        if (cedulaStr.length() < 7 || cedulaStr.length() > 10)
            throw invalid_argument("La cédula debe tener entre 7 y 10 dígitos.");
        cedula = stol(cedulaStr);

        cout << "Ingrese su clave: ";
        cin >> clave;

        if (clave.length() == 10) {
            Anfitrion** anfitriones = sistema.getAnfitriones();
            int total = sistema.getTotalAnfitriones();
            for (int i = 0; i < total; i++) {
                if (anfitriones[i]->getCedula() == cedula) {
                    if (anfitriones[i]->getClave() == clave) {
                        cout << "\nIngreso exitoso como ANFITRIÓN\n";
                        menuAnfitrion(anfitriones[i]);
                        return;
                    } else {
                        throw runtime_error("Problema de credenciales.");
                    }
                }
            }
            throw runtime_error("Usuario no encontrado.");
        } else if (clave.length() == 7) {
            Usuario** usuarios = sistema.getUsuarios();
            int total = sistema.getTotalUsuarios();
            for (int i = 0; i < total; i++) {
                if (usuarios[i]->getCedula() == cedula) {
                    if (usuarios[i]->getClave() == clave) {
                        cout << "\nIngreso exitoso como USUARIO\n";
                        menuUsuario(usuarios[i]);
                        return;
                    } else {
                        throw runtime_error("Problema de credenciales.");
                    }
                }
            }
            throw runtime_error("Usuario no encontrado.");
        } else {
            throw runtime_error("Longitud de clave no válida.");
        }

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }
}

int main() {
    CargaDatos sistema;

    sistema.cargarAlojamientos("alojamientos.txt");
    sistema.cargarAnfitriones("anfitriones.txt");
    sistema.cargarUsuarios("usuarios.txt");
    sistema.cargarReservaciones("reservas.txt");

    menuPrincipal(sistema);

    return 0;
}
