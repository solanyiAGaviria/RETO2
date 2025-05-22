#include <QCoreApplication>
#include "usuarios.h"
#include "anfitrion.h"
#include "funciones.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>




int main() {


    //crear primero alojamientos
    //anfitriones
    //clientes
    //reservas



    //CARGA DE ALOJAMIENTOS---------------------

        alojamiento* alojamientos = nullptr;
        int total = 0;

        cargar_alojamientos(alojamientos, total);

        cout << "Total alojamientos cargados: " << total << endl;

        // Mostrar algunos para verificar
        for (int i = 0; i < total; ++i) {
            alojamientos[i].mostrar();
        }

        delete[] alojamientos;





    //CARGA DE ANFITRIONES
        int cantidad = 0;
        anfitrion* anfitriones = cargarAnfitriones("anfitriones.txt", cantidad);

        if (anfitriones == nullptr) {
            std::cout << "Error al abrir el archivo.\n";
            return 1;
        }

        for (int i = 0; i < cantidad; i++) {
            std::cout << "\nAnfitrión " << (i + 1) << ":\n";
            anfitriones[i].mostrar();
        }

        delete[] anfitriones;
        return 0;
}


















    /*

    const int MAX_USUARIOS = 100;
    Usuarios** usuarios = new Usuarios*[MAX_USUARIOS];
    int cantidad = 0;

    std::ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return 1;
    }

    std::string linea;
    std::getline(archivo, linea); // Saltar la línea del encabezado

    while (std::getline(archivo, linea) && cantidad < MAX_USUARIOS) {
        usuarios[cantidad] = Usuarios::desdeLinea(linea);
        cantidad++;
    }

    archivo.close();

    std::cout << "\nUsuarios cargados:\n";
    for (int i = 0; i < cantidad; ++i) {
        std::cout << "Usuario " << i + 1 << ": ";
        usuarios[i]->mostrar();
    }

    // Liberar memoria
    for (int i = 0; i < cantidad; ++i) {
        delete usuarios[i];
    }
    delete[] usuarios;



*/









