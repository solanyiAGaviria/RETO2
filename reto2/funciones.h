#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "alojamientos.h"
#include "anfitrion.h"

anfitrion* cargarAnfitriones(const char* nombreArchivo, int& cantidad);

void cargar_alojamientos(alojamiento*& alojamientos, int& total);

#endif


