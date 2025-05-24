#ifndef FECHA_H
#define FECHA_H

class fecha {
private:
    int dia;
    int mes;
    int anio;

    bool es_bisiesto(int anio) const;
    int dias_en_mes(int mes, int anio) const;

public:
    fecha(); // Constructor por defecto
    fecha(int d, int m, int a); // Constructor con parámetros

    bool es_valida() const;
    void sumar_dias(int n);
    void obtener_cadena(char* buffer) const; // Devuelve la fecha como "dd/mm/aaaa"
};

#endif
