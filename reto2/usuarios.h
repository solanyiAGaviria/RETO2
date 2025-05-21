#ifndef USUARIOS_H
#define USUARIOS_H
#include "reservas.h"

class usuarios {
public:

    //modificar algunos a privados
    char documento[20];
    char clave[20];
    int tiempoplat;
    float puntuacion;

    usuarios();
    usuarios::usuarios(const char* doc, const char* pass, int tiempo, float punt);
    void mostrarDatos();
};











#endif

