// Reservacion.h
#ifndef RESERVACION_H
#define RESERVACION_H

#include <string>
#include "Fecha.h"

class Reservacion {
private:
    std::string codigo;
    int cedula_usuario;
    int id_alojamiento;
    Fecha fecha_pago;
    std::string metodo_pago;
    Fecha fecha_inicio;
    Fecha fecha_fin;
    std::string pregunta_cliente;

public:
    Reservacion();
    Reservacion(const std::string& cod, int cedula, int id_aloja,
                const Fecha& pago, const std::string& metodo,
                const Fecha& inicio, const Fecha& fin,
                const std::string& pregunta);
    Reservacion(const std::string& codGenerico);
    Reservacion(const Reservacion &otra);
    ~Reservacion();

    std::string getCodigo() const;
    int getCedulaUsuario() const;
    int getIdAlojamiento() const;
    Fecha getFechaPago() const;
    std::string getMetodoPago() const;
    Fecha getFechaInicio() const;
    Fecha getFechaFin() const;
    std::string getPregunta() const;

    void setCodigo(const std::string& cod);
    void setCedulaUsuario(long ced);
    void setIdAlojamiento(int id);
    void setFechaPago(const Fecha& f);
    void setMetodoPago(const std::string& m);
    void setFechaInicio(const Fecha& f);
    void setFechaFin(const Fecha& f);
    void setPregunta(const std::string& p);

    Reservacion& operator=(const Reservacion &otra);

    void mostrarComprobante() const;
    bool esGenerica() const;
};

#endif // RESERVACION_H
