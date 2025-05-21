#include "funciones.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstring>

int cantlineas(const* string nombrearch){
        FILE* archivo = fopen(nombrearch, "r");
        if (!archivo) {
            std::cerr << "No se pudo abrir el archivo\n";
            return -1;
        }

        const int TAM = 1024;
        char buffer[TAM];
        int contador = 0;

        while (fgets(buffer, TAM, archivo)) {
            contador++;
        }

        fclose(archivo);
        return contador;
    }



