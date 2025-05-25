// main.cpp
#include <iostream>
#include <string>
#include "CargaDatos.h"

using namespace std;

void menuUsuario(CargaDatos& sistema, Usuario* usuario) {
    int opcion;
    do {
        cout << "\n--- Menú Usuario ---\n";
        cout << "1. Reservar alojamiento con filtros\n";
        cout << "2. Reservar por código de alojamiento\n";
        cout << "3. Mostrar mis reservaciones\n";
        cout << "4. Anular una reservación\n";
        cout << "5. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            sistema.reservarConFiltros(usuario);
            break;
        case 2:
            sistema.reservarPorCodigo(usuario);
            break;
        case 3:
            usuario->mostrarReservas();
            break;
        case 4:
            sistema.anularReserva(usuario);
            break;
        case 5:
            cout << "Saliendo del menú de usuario...\n";
            break;
        default:
            cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 5);
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
            Anfitrion* anfitrion = sistema.buscarAnfitrionPorCedula(cedula);
            if (anfitrion) {
                if (anfitrion->getClave() == clave) {
                    cout << "\nIngreso exitoso como ANFITRIÓN\n";
                    menuAnfitrion(anfitrion);
                    return;
                } else {
                    throw runtime_error("Problema de credenciales.");
                }
            } else {
                throw runtime_error("Usuario no encontrado.");
            }

        } else if (clave.length() == 7) {
            Usuario* usuario = sistema.buscarUsuarioPorCedula(cedula);
            if (usuario) {
                if (usuario->getClave() == clave) {
                    cout << "\nIngreso exitoso como USUARIO\n";
                    menuUsuario(sistema, usuario);
                    return;
                } else {
                    throw runtime_error("Problema de credenciales.");
                }
            } else {
                throw runtime_error("Usuario no encontrado.");
            }

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
