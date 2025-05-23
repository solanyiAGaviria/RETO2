#include "Red.h"
#include <iostream>

using namespace std;

char idANombre(int id) {
    return static_cast<char>('A' + id);
}

int nombreAId(char nombre) {
    return static_cast<int>(toupper(nombre) - 'A');
}

void mostrarMenu() {
    cout << "\n--- Simulador de Red de Enrutadores ---" << endl;
    cout << "1. Cargar red desde archivo" << endl;
    cout << "2. Agregar router" << endl;
    cout << "3. Eliminar router" << endl;
    cout << "4. Conectar routers" << endl;
    cout << "5. Calcular rutas" << endl;
    cout << "6. Obtener costo entre routers" << endl;
    cout << "7. Obtener ruta entre routers" << endl;
    cout << "8. Mostrar tabla absoluta" << endl;
    cout << "9. Mostrar tabla relativa" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    Red red;
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string archivo;
            cout << "Ingrese el nombre del archivo: ";
            cin >> archivo;
            red.cargarDesdeArchivo(archivo);
            red.calcularRutas();
            break;
        }
        case 2: {
            char nombre;
            cout << "Letra del router a agregar (ej. A): ";
            cin >> nombre;
            red.agregarRouter(nombreAId(nombre));
            break;
        }
        case 3: {
            char nombre;
            cout << "Letra del router a eliminar (ej. A): ";
            cin >> nombre;
            red.eliminarRouter(nombreAId(nombre));
            break;
        }
        case 4: {
            char nombre1, nombre2;
            int costo;
            cout << "Letra del primer router: ";
            cin >> nombre1;
            cout << "Letra del segundo router: ";
            cin >> nombre2;
            cout << "Costo del enlace: ";
            cin >> costo;
            red.conectar(nombreAId(nombre1), nombreAId(nombre2), costo);
            break;
        }
        case 5: {
            red.calcularRutas();
            cout << "Rutas calculadas." << endl;
            break;
        }
        case 6: {
            char origen, destino;
            cout << "Letra del router origen: ";
            cin >> origen;
            cout << "Letra del router destino: ";
            cin >> destino;
            int costo = red.obtenerCosto(nombreAId(origen), nombreAId(destino));
            if (costo >= 0)
                cout << "Costo: " << costo << endl;
            else
                cout << "Ruta no encontrada." << endl;
            break;
        }
        case 7: {
            char origen, destino;
            cout << "Letra del router origen: ";
            cin >> origen;
            cout << "Letra del router destino: ";
            cin >> destino;
            vector<int> ruta = red.obtenerRuta(nombreAId(origen), nombreAId(destino));
            if (!ruta.empty()) {
                cout << "Ruta: ";
                for (size_t i = 0; i < ruta.size(); ++i) {
                    cout << idANombre(ruta[i]);
                    if (i != ruta.size() - 1) cout << " -> ";
                }
                cout << endl;
            } else {
                cout << "Ruta no encontrada." << endl;
            }
            break;
        }
        case 8: {
            red.mostrarTablaAbsoluta();
            break;
        }
        case 9: {
            red.mostrarTablaRelativa();
            break;
        }
        case 0:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
            break;
        }
    } while (opcion != 0);

    return 0;
}
