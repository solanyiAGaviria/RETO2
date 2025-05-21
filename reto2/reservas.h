/*#ifndef RESERVAS_H
#define RESERVAS_H
#include "alojamientos.h"
// No incluyas "usuarios.h" aquí directamente si ya reservas está incluida allá → evitar recursividad
class reservas {
public:
    char fechaEntrada[15];
    int duracion;
    char codReserva[10];
    char codAlojamiento[10];
    char docUsuario[20];
    char metodoPago[15];
    char fechaPago[15];
    int monto;
    char anotaciones[1000];

    reservas();
    reservas(const char* fecha, int dur, const char* codRes, const char* codAloj, const char* docUsu,
             const char* metodo, const char* fechaPay, int montoP, const char* nota);
    void mostrarComprobante();
};

















/*
class reservas {
public:
    char fechaEntrada[15];
    int duracion;
    char codReserva[10];
    char codAlojamiento[10];
    char docUsuario[20];
    char metodoPago[15];
    char fechaPago[15];
    int monto;
    char anotaciones[1000];

    reservas();
    reservas(const char* fecha, int dur, const char* codRes, const char* codAloj, const char* docUsu,
             const char* metodo, const char* fechaPay, int montoP, const char* nota);
    void mostrarComprobante();
};*/























/*class reservas
{
public:
    reservas(); // Constructor por defecto
    reservas(const char* fechaEnt, const char* anotaciones, const char* metodoPago,
             unsigned int noches, const char* codReserva, const char* fechaPago,
             unsigned int monto, const char* codAlojamiento, const char* docUsuario);

    void mostrarComprobante(); // Método para mostrar información de la reserva

    // Relaciones con otras clases
    alojamientos* alojamiento; // Puntero al alojamiento asociado
    // usuarios* usuario; // Si lo necesitas (mejor evitar doble inclusión cruzada aquí)

private:
    char fechaEnt[20];
    char anotaciones[100];
    char metodoPago[20];

    unsigned int numNoches;
    char codReserva[10];
    char fechaPago[20];
    unsigned int monto;
    char codAlojamiento[10];
    char docUsuario[20];
};
*/


//#endif // RESERVAS_H

