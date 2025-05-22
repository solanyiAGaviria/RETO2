#ifndef ANFITRION_H
#define ANFITRION_H

#include <string>

class anfitrion {
private:
    std::string cedula;
    std::string clave;
    std::string* alojamientos;
    int cantidadAlojamientos;

public:
    int antiguedad_meses;
    float calificacion;

    anfitrion();
    anfitrion(std::string ced, std::string cla, int antig, float calif, std::string* aloj, int cant);
    ~anfitrion();
    void mostrar() const;
};

#endif
