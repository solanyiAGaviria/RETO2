#include "base_datos.h"
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <string>

using namespace std;
void generarTopologiaAleatoria(const string& archivo, int cantidadRouters) {
    ofstream salida(archivo);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distCosto(1, 10);

    for (int i = 0; i < cantidadRouters; ++i) {
        for (int j = i + 1; j < cantidadRouters; ++j) {
            if (rand() % 2 == 0) { // 50% probabilidad de crear enlace
                int costo = distCosto(gen);
                salida << idANombre(i) << " " << idANombre(j) << " " << costo << endl;
            }
        }
    }
    salida.close();
}


