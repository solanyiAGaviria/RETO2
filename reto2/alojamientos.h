#ifndef ALOJAMIENTOS_H
#define ALOJAMIENTOS_H

#include <string>
using namespace std;

class alojamiento {
public:
    string id;
    string nombre;
    string departamento;
    string municipio;
    string tipo;
    string direccion;
    string precio_noche;
    string amenidades;

    alojamiento(); // Constructor por defecto
    alojamiento(string linea); // Constructor desde línea de archivo

    void mostrar() const;
};

#endif




























/*class alojamientos {



    public:
    char nombre;
    char codigo;
    char departamento;
    char municipio;
    char tipoCasa;
    char direccion;
    int precioNoche;
    char amenidades;
    char fechasFuturas;


    alojamientos();
    ~alojamientos();



private:
    //array de punteros
};*/




