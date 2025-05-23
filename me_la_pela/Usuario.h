// Usuario.h
#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "Reservacion.h"

#define MAX_RESERVAS_USUARIO 100

class Usuario {
private:
    long cedula;
    std::string nombre;
    std::string clave;
    float calificacion;
    Reservacion** reservas;
    int cantidadReservas;

public:
    Usuario();
    Usuario(long ced, const std::string& nom, const std::string& clave_, float calif);
    Usuario(const Usuario &otro);
    ~Usuario();

    long getCedula() const;
    std::string getNombre() const;
    std::string getClave() const;
    float getCalificacion() const;
    Reservacion** getReservas();
    int getCantidadReservas() const;

    void setCedula(long c);
    void setNombre(const std::string& n);
    void setClave(const std::string& c);
    void setCalificacion(float cal);

    Usuario& operator=(const Usuario &otro);

    void añadirReserva(Reservacion* r);
    void quitarReserva(const std::string& codigoReserva);
    void mostrarReservas() const;
    void mostrarUsuario() const;
};

#endif // USUARIO_H
