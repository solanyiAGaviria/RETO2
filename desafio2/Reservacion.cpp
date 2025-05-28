// Reservacion.cpp
#include "Reservacion.h"
#include <iostream>

Reservacion::Reservacion() : cedula_usuario(0), id_alojamiento(0), metodo_pago(""), pregunta_cliente("") {}

Reservacion::Reservacion(const std::string& cod, long cedula, int id_aloja,
                         const Fecha& pago, const std::string& metodo,
                         const Fecha& inicio, const Fecha& fin,
                         const std::string& pregunta)
    : codigo(cod), cedula_usuario(cedula), id_alojamiento(id_aloja),
    fecha_pago(pago), metodo_pago(metodo), fecha_inicio(inicio), fecha_fin(fin), pregunta_cliente(pregunta) {}

Reservacion::Reservacion(const std::string& codGenerico)
    : codigo(codGenerico), cedula_usuario(0), id_alojamiento(0), metodo_pago("GEN"), pregunta_cliente("") {}

Reservacion::Reservacion(const Reservacion &otra)
    : codigo(otra.codigo), cedula_usuario(otra.cedula_usuario), id_alojamiento(otra.id_alojamiento),
    fecha_pago(otra.fecha_pago), metodo_pago(otra.metodo_pago),
    fecha_inicio(otra.fecha_inicio), fecha_fin(otra.fecha_fin), pregunta_cliente(otra.pregunta_cliente) {}

Reservacion::~Reservacion() {}

std::string Reservacion::getCodigo() const { return codigo; }
long Reservacion::getCedulaUsuario() const { return cedula_usuario; }
int Reservacion::getIdAlojamiento() const { return id_alojamiento; }
Fecha Reservacion::getFechaPago() const { return fecha_pago; }
std::string Reservacion::getMetodoPago() const { return metodo_pago; }
Fecha Reservacion::getFechaInicio() const { return fecha_inicio; }
Fecha Reservacion::getFechaFin() const { return fecha_fin; }
std::string Reservacion::getPregunta() const { return pregunta_cliente; }

void Reservacion::setCodigo(const std::string& cod) { codigo = cod; }
void Reservacion::setCedulaUsuario(long ced) { cedula_usuario = ced; }
void Reservacion::setIdAlojamiento(int id) { id_alojamiento = id; }
void Reservacion::setFechaPago(const Fecha& f) { fecha_pago = f; }
void Reservacion::setMetodoPago(const std::string& m) { metodo_pago = m; }
void Reservacion::setFechaInicio(const Fecha& f) { fecha_inicio = f; }
void Reservacion::setFechaFin(const Fecha& f) { fecha_fin = f; }
void Reservacion::setPregunta(const std::string& p) { pregunta_cliente = p; }

Reservacion& Reservacion::operator=(const Reservacion &otra) {
    if (this != &otra) {
        codigo = otra.codigo;
        cedula_usuario = otra.cedula_usuario;
        id_alojamiento = otra.id_alojamiento;
        fecha_pago = otra.fecha_pago;
        metodo_pago = otra.metodo_pago;
        fecha_inicio = otra.fecha_inicio;
        fecha_fin = otra.fecha_fin;
        pregunta_cliente = otra.pregunta_cliente;
    }
    return *this;
}

void Reservacion::mostrarComprobante() const {
    std::cout << "\n--- COMPROBANTE DE RESERVA ---\n";
    std::cout << "+Codigo: " << codigo << "\n";
    std::cout << "+Cedula del usuario: " << cedula_usuario << "\n";
    std::cout << "ID del alojamiento: " << id_alojamiento << "\n";
    std::cout << "Fecha de pago: "; fecha_pago.mostrarDiaMes();
    std::cout << "Metodo de pago: " << metodo_pago << "\n";
    std::cout << "Fecha de inicio: "; fecha_inicio.mostrarDiaMes();
    std::cout << "Fecha de fin: "; fecha_fin.mostrarDiaMes();
    std::cout << "Pregunta del cliente: " << pregunta_cliente << "\n";
}

bool Reservacion::esGenerica() const {
    return metodo_pago == "GEN";
}
