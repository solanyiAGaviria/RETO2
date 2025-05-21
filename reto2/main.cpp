#include <QCoreApplication>
#include "usuarios.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


const int MAX_USUARIOS = 100;

int main() {
    usuario usuarios[100];
    int count = 0;

    std::ifstream archivo("usuarios.txt");
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo.\n";
        return 1;
    }

    std::string linea;
    while (std::getline(archivo, linea) && count < MAX_USUARIOS) {
        std::stringstream ss(linea);
        std::string nombre, doc, clave, tiempo, puntuacion, id;

        std::getline(ss, nombre, ',');
        std::getline(ss, doc, ',');
        std::getline(ss, clave, ',');
        std::getline(ss, tiempo, ',');
        std::getline(ss, puntuacion, ',');
        std::getline(ss, id, ',');

        usuarios[count] = usuarios(nombre, doc, clave, tiempo, puntuacion, id);
        count++;
    }

    archivo.close();

    std::cout << "\nUsuarios cargados:\n";
    for (int i = 0; i < count; ++i) {
        usuarios[i].mostrar();
    }

    return 0;
}
