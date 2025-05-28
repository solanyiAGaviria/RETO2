#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "Reservacion.h"

class Usuario {
private:
    int cedula;
    std::string nombre;
    std::string clave;
    float calificacion;

    Reservacion** reservas;
    int cantidadReservas;
    int capacidadReservas;

    void redimensionarReservas();  // ✅ redimensionamiento interno

public:
    Usuario();
    Usuario(int ced, const std::string& nom, const std::string& clave_, float calif);
    Usuario(const Usuario& otro);
    ~Usuario();

    int getCedula() const;
    std::string getNombre() const;
    std::string getClave() const;
    float getCalificacion() const;
    int getCantidadReservas() const;
    Reservacion** getReservas();
    Reservacion* getReserva(int index) const;

    void setCedula(long c);
    void setNombre(const std::string& n);
    void setClave(const std::string& c);
    void setCalificacion(float cal);

    void añadirReserva(Reservacion* r);
    void quitarReserva(const std::string& codigo);
    void resetReservas();  // ✅ para refrescar estructura

    void mostrarUsuario() const;
    void mostrarReservas() const;

    Usuario& operator=(const Usuario& otro);
};

#endif
