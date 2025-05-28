#ifndef ANFITRION_H
#define ANFITRION_H

#include <string>
#include "Alojamiento.h"

class Anfitrion {
private:
    int cedula;
    std::string nombre;
    std::string clave;
    int antiguedad_meses;
    float calificacion;

    Alojamiento** alojamientos;
    int cantidadAlojamientos;
    int capacidadAlojamientos;  // ✅ Capacidad dinámica

    void redimensionarAlojamientos();  // ✅ Método interno de expansión

public:
    Anfitrion();
    Anfitrion(int ced, const std::string& nom, const std::string& clave_, int ant, float calif);
    Anfitrion(const Anfitrion& otro);
    ~Anfitrion();

    int getCedula() const;
    std::string getNombre() const;
    std::string getClave() const;
    int getAntiguedad() const;
    float getCalificacion() const;
    int getCantidadAlojamientos() const;
    Alojamiento** getAlojamientos();
    Alojamiento* getAlojamiento(int index) const;

    void setCedula(long c);
    void setNombre(const std::string& n);
    void setClave(const std::string& c);
    void setAntiguedad(int a);
    void setCalificacion(float cal);

    void añadirAlojamiento(Alojamiento* a);

    void mostrarAnfitrion() const;
    void mostrarCaracteristicas() const;

    Anfitrion& operator=(const Anfitrion& otro);
};

#endif
