#ifndef ANFITRION_H
#define ANFITRION_H

#include <string>
#include "Alojamiento.h"

#define MAX_ALOJAMIENTOS 100

class Alojamiento; // Declaración adelantada

class Anfitrion {
private:
    long cedula;
    std::string nombre;
    std::string clave;
    int antiguedad_meses;
    float calificacion;
    Alojamiento** alojamientos;
    int cantidadAlojamientos;

public:
    Anfitrion();
    Anfitrion(long ced, const std::string& nom, const std::string& clave_, int ant, float calif);
    Anfitrion(const Anfitrion &otro);
    ~Anfitrion();

    // Getters
    long getCedula() const;
    std::string getNombre() const;
    std::string getClave() const;
    int getAntiguedad() const;
    float getCalificacion() const;
    int getCantidadAlojamientos() const;
    Alojamiento** getAlojamientos();

    // Setters
    void setCedula(long c);
    void setNombre(const std::string& n);
    void setClave(const std::string& c);
    void setAntiguedad(int a);
    void setCalificacion(float cal);

    // Operador de asignación
    Anfitrion& operator=(const Anfitrion &otro);

    // Métodos
    void añadirAlojamiento(Alojamiento* a);
    void mostrarAnfitrion() const;
    void mostrarCaracteristicas() const;
};

#endif // ANFITRION_H
