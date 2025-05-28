// main.cpp
#include <iostream>
#include <string>
#include "CargaDatos.h"

using namespace std;

void menuUsuario(CargaDatos& sistema, Usuario* usuario) {
    int opcion;
    usuario->mostrarUsuario();
    do {
        cout << "\n--- Menu Usuario ---\n";
        cout << "1. Reservar alojamiento con filtros\n";
        cout << "2. Reservar por codigo de alojamiento\n";
        cout << "3. Mostrar mis reservaciones\n";
        cout << "4. Anular una reservacion\n";
        cout << "5. Salir\n";
        cout << "Opcion: ";
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
            cout << "Saliendo del menu de usuario...\n";
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 5);
}

void menuAnfitrion(CargaDatos& sistema, Anfitrion* anfitrion) {
    int opcion;
    anfitrion->mostrarCaracteristicas();
    do {
        cout << "\n--- Menu Anfitrion ---\n";
        cout << "1. Consultar reservaciones\n";
        cout << "2. Eliminar reservacion\n";
        cout << "3. Actualizar historico\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            sistema.consultarReservacionesAnfitrion(anfitrion);
            break;
        case 2:
            sistema.eliminarReservacionAnfitrion(anfitrion);
            break;
        case 3:
            sistema.actualizarHistorico(anfitrion);
            sistema.refrescarEstructura();
            break;
        case 4:
            cout << "Saliendo del menu de anfitrion...\n";
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 4);
}

void menuPrincipal(CargaDatos& sistema) {
    string cedulaStr, clave;
    long cedula;
    int opcion;

    cout << "===== Bienvenido a UdeAStay =====\n";
    cout << "1. Iniciar sesion\n";
    cout << "2. Salir\n";
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    if (opcion == 2) return;

    try {
        cout << "Ingrese su cedula: ";
        cin >> cedulaStr;
        if (cedulaStr.length() < 7 || cedulaStr.length() > 10)
            throw invalid_argument("La cedula debe tener entre 7 y 10 digitos.");
        cedula = stol(cedulaStr);

        cout << "Ingrese su clave: ";
        cin >> clave;

        if (clave.length() == 10) {
            Anfitrion* anfitrion = sistema.buscarAnfitrionPorCedula(cedula);
            if (anfitrion) {
                if (anfitrion->getClave() == clave) {
                    cout << "\nIngreso exitoso como ANFITRION\n";
                    menuAnfitrion(sistema, anfitrion);
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
            throw runtime_error("Longitud de clave no valida.");
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

    sistema.guardarReservasEnArchivo("reservas.txt");


    return 0;
}
