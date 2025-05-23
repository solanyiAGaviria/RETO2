#include "Fecha.h"
#include <iostream>
#include <string>

using namespace std;

// Constructor sin parámetros (inicializa en una fecha inválida)
Fecha::Fecha() {
    dia = 0;
    mes = 0;
    anio = 0;
}

// Constructor con parámetros
Fecha::Fecha(int d, int m, int a) {
    dia = d;
    mes = m;
    anio = a;
}

// Constructor de copia
Fecha::Fecha(const Fecha &otra) {
    dia = otra.dia;
    mes = otra.mes;
    anio = otra.anio;
}

// Destructor
Fecha::~Fecha() {}

// Setters
void Fecha::setDia(int d) { dia = d; }
void Fecha::setMes(int m) { mes = m; }
void Fecha::setAnio(int a) { anio = a; }

// Getters
int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

// Operador asignación
Fecha& Fecha::operator=(const Fecha &otra) {
    if (this != &otra) {
        dia = otra.dia;
        mes = otra.mes;
        anio = otra.anio;
    }
    return *this;
}

// Operadores de comparación
bool Fecha::operator<(const Fecha &otra) const {
    if (anio < otra.anio) return true;
    if (anio == otra.anio && mes < otra.mes) return true;
    if (anio == otra.anio && mes == otra.mes && dia < otra.dia) return true;
    return false;
}

bool Fecha::operator>(const Fecha &otra) const {
    return otra < *this;
}

bool Fecha::operator==(const Fecha &otra) const {
    return (dia == otra.dia && mes == otra.mes && anio == otra.anio);
}

// Verifica si la fecha es válida (considera años bisiestos)
bool Fecha::fechaValida() const {
    if (anio < 1900 || mes < 1 || mes > 12 || dia < 1)
        return false;

    int diasMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    bool bisiesto = (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));

    if (bisiesto && mes == 2)
        return dia <= 29;
    else
        return dia <= diasMes[mes - 1];
}

// Verifica si la fecha actual está entre dos fechas
bool Fecha::compararFechas(const Fecha &inicio, const Fecha &fin) const {
    return (*this > inicio && *this < fin);
}

// Retorna el nombre del mes y día de la semana
void Fecha::mostrarDiaMes() const {
    const string diasSemana[] = { "Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado" };
    const string meses[] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                            "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre" };

    // Algoritmo de Zeller para calcular día de la semana
    int m = mes;
    int y = anio;
    if (m < 3) {
        m += 12;
        y--;
    }

    int k = y % 100;
    int j = y / 100;
    int h = (dia + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    int diaSemana = (h + 6) % 7;

    cout << diasSemana[diaSemana] << ", " << dia << " de " << meses[mes - 1] << " del " << anio << endl;
}

// Suma días a la fecha y retorna la nueva fecha
Fecha Fecha::sumarDias(int diasSumar) const {
    int d = dia, m = mes, a = anio;
    int diasMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    while (diasSumar > 0) {
        bool bisiesto = (a % 4 == 0 && (a % 100 != 0 || a % 400 == 0));
        int diasEnMes = diasMes[m - 1];
        if (bisiesto && m == 2) diasEnMes++;

        if (d + diasSumar <= diasEnMes) {
            d += diasSumar;
            diasSumar = 0;
        } else {
            diasSumar -= (diasEnMes - d + 1);
            d = 1;
            m++;
            if (m > 12) {
                m = 1;
                a++;
            }
        }
    }

    return Fecha(d, m, a);
}
