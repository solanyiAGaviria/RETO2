// Alojamiento.h
#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include <string>
#include "Reservacion.h"

class Anfitrion; // Declaración adelantada

class Alojamiento {
private:
    int id_alojamiento;
    std::string nombre;
    std::string departamento;
    std::string municipio;
    std::string tipo;
    std::string direccion;
    int precio_noche;
    std::string amenidades;

    Anfitrion* anfitrion;
    Reservacion** reservas;
    int cantidadReservas;

public:
    Alojamiento();
    Alojamiento(int id, const std::string& nom, const std::string& dep, const std::string& mun, const std::string& tipo_,
                const std::string& dir, int precio, const std::string& amenidades_);
    Alojamiento(const Alojamiento &otro);
    ~Alojamiento();

    // Getters
    int getId() const;
    std::string getNombre() const;
    std::string getDepartamento() const;
    std::string getMunicipio() const;
    std::string getTipo() const;
    std::string getDireccion() const;
    int getPrecioNoche() const;
    std::string getAmenidades() const;

    // Setters
    void setId(int id);
    void setNombre(const std::string& nom);
    void setDepartamento(const std::string& dep);
    void setMunicipio(const std::string& mun);
    void setTipo(const std::string& t);
    void setDireccion(const std::string& dir);
    void setPrecioNoche(int precio);
    void setAmenidades(const std::string& amen);

    void setAnfitrion(Anfitrion* a);
    Anfitrion* getAnfitrion() const;

    Alojamiento& operator=(const Alojamiento &otro);

    void añadirReserva(Reservacion* r);
    void quitarReserva(const std::string& codigoReserva);
    void mostrarAlojamiento() const;
    void misReservas() const;
    void fechasDisponibles(const Fecha& hoy) const;

    Reservacion** getReservas();
    int getCantidadReservas() const;
};

#endif // ALOJAMIENTO_H
