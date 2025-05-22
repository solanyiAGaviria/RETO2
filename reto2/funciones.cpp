#include "funciones.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

//ALOJAMIENTOS
void cargar_alojamientos(alojamiento*& alojamientos, int& total) {
    ifstream archivo("alojamientos.txt");
    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        total = 0;
        alojamientos = nullptr;
        return;
    }

    string linea;
    getline(archivo, linea); // Saltar línea de encabezado

    total = 0;
    while (getline(archivo, linea)) {
        if (!linea.empty()) total++;
    }

    archivo.clear();
    archivo.seekg(0);
    getline(archivo, linea); // Saltar encabezado otra vez

    alojamientos = new alojamiento[total];
    int i = 0;
    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            alojamientos[i] = alojamiento(linea);
            i++;
        }
    }

    archivo.close();
}


//ANFITRIONES

anfitrion* cargarAnfitriones(const char* nombreArchivo, int& cantidad) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cantidad = 0;
        return nullptr;
    }

    std::string linea;
    getline(archivo, linea); // saltar encabezado

    // Primero contar líneas
    cantidad = 0;
    while (getline(archivo, linea)) {
        cantidad++;
    }

    archivo.clear();
    archivo.seekg(0);
    getline(archivo, linea); // saltar encabezado otra vez

    anfitrion* arreglo = new anfitrion[cantidad];
    int indice = 0;

    while (getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string cedula, clave, strAntig, strCalif, codigos;

        getline(ss, cedula, ';');
        getline(ss, clave, ';');
        getline(ss, strAntig, ';');
        getline(ss, strCalif, ';');
        getline(ss, codigos);

        int antig = std::stoi(strAntig);
        float calif = std::stof(strCalif);

        // Separar alojamientos
        int cantidadAlojamientos = 1;
        for (size_t i = 0; i < codigos.length(); i++) {
            if (codigos[i] == ',') cantidadAlojamientos++;
        }

        std::string* alojamientos = new std::string[cantidadAlojamientos];
        std::stringstream ssAlo(codigos);
        std::string token;
        int idx = 0;
        while (getline(ssAlo, token, ',')) {
            alojamientos[idx++] = token;
        }

        arreglo[indice++] = anfitrion(cedula, clave, antig, calif, alojamientos, cantidadAlojamientos);
        delete[] alojamientos;
    }

    archivo.close();
    return arreglo;
}


