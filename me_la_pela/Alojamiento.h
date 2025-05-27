#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include <string>
#include "Reservacion.h"

class Anfitrion;  // declaración adelantada

class Alojamiento {
private:
    int id;
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
    int capacidadReservas;

    void redimensionarReservas();

public:
    Alojamiento();
    Alojamiento(int id_, const std::string& nombre_, const std::string& dep, const std::string& mun,
                const std::string& tipo_, const std::string& dir, int precio, const std::string& amen);
    Alojamiento(const Alojamiento& otro);
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
    Anfitrion* getAnfitrion() const;
    int getCantidadReservas() const;
    Reservacion** getReservas();
    Reservacion* getReserva(int index) const;

    // Setters
    void setAnfitrion(Anfitrion* a);
    void setPrecioNoche(int p);

    // Métodos
    void añadirReserva(Reservacion* r);
    void quitarReserva(const std::string& codigo);
    void resetReservas();

    void mostrarAlojamiento() const;
    void misReservas() const;
    void fechasDisponibles(const Fecha& desde) const;
    bool estaDisponible(const Fecha& f, const Fecha& hoy) const;

    Alojamiento& operator=(const Alojamiento& otro);
};

#endif
