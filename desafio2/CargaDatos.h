#ifndef CARGADATOS_H
#define CARGADATOS_H

#include <string>
#include "Alojamiento.h"
#include "Anfitrion.h"
#include "Usuario.h"
#include "Reservacion.h"



class CargaDatos {
private:
    Alojamiento** alojamientos;
    int totalAlojamientos;

    Anfitrion** anfitriones;
    int totalAnfitriones;

    Usuario** usuarios;
    int totalUsuarios;

    Reservacion** reservas;
    int totalReservas;

    int siguienteIdReserva;
    int capacidadAlojamientos;
    int capacidadAnfitriones;
    int capacidadUsuarios;
    int capacidadReservas;



public:
    CargaDatos();
    ~CargaDatos();

    void cargarAlojamientos(const std::string& ruta);
    void cargarAnfitriones(const std::string& ruta);
    void cargarUsuarios(const std::string& ruta);
    void cargarReservaciones(const std::string& ruta);
    void redimensionarAlojamientos();
    void redimensionarAnfitriones();
    void redimensionarUsuarios();
    void  redimensionarReservas();

    Alojamiento** getAlojamientos();
    int getTotalAlojamientos() const;

    Anfitrion** getAnfitriones();
    int getTotalAnfitriones() const;

    Usuario** getUsuarios();
    int getTotalUsuarios() const;

    Reservacion** getReservas();
    int getTotalReservas() const;

    void incrementarTotalReservas();

    Alojamiento* buscarAlojamientoPorId(int id);
    Usuario* buscarUsuarioPorCedula(int cedula);
    Anfitrion* buscarAnfitrionPorCedula(int cedula);
    void reservarConFiltros(Usuario* usuario);
    void refrescarEstructura();
    void guardarReservasEnArchivo(const std::string& ruta);



    void reservarPorCodigo(Usuario* usuario);
    void anularReserva(Usuario* usuario);
    // Funcionalidade anfritrion
    void consultarReservacionesAnfitrion(Anfitrion* anfitrion);
    void eliminarReservacionAnfitrion(Anfitrion* anfitrion);
    void actualizarHistorico(Anfitrion* anfitrion);

};

#endif // CARGADATOS_H
