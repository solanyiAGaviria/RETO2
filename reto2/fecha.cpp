#include "fecha.h"
#include <cstdio>

fecha::fecha() : dia(1), mes(1), anio(2000) {}

fecha::fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}

bool fecha::es_bisiesto(int anio) const {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

int fecha::dias_en_mes(int mes, int anio) const {
    switch(mes) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        return es_bisiesto(anio) ? 29 : 28;
    default:
        return 0;
    }
}

bool fecha::es_valida() const {
    if (anio < 1 || mes < 1 || mes > 12 || dia < 1)
        return false;
    return dia <= dias_en_mes(mes, anio);
}

void fecha::sumar_dias(int n) {
    dia += n;
    while (dia > dias_en_mes(mes, anio)) {
        dia -= dias_en_mes(mes, anio);
        mes++;
        if (mes > 12) {
            mes = 1;
            anio++;
        }
    }
}

void fecha::obtener_cadena(char* buffer) const {
    std::sprintf(buffer, "%02d/%02d/%04d", dia, mes, anio);
}
