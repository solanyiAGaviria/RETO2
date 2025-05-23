// Fecha.h
#ifndef FECHA_H
#define FECHA_H

class Fecha {
private:
    int dia, mes, anio;

public:
    Fecha();
    Fecha(int d, int m, int a);
    Fecha(const Fecha &otra);
    ~Fecha();

    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);
    int getDia() const;
    int getMes() const;
    int getAnio() const;

    bool operator<(const Fecha &otra) const;
    bool operator>(const Fecha &otra) const;
    bool operator==(const Fecha &otra) const;
    Fecha& operator=(const Fecha &otra);

    bool fechaValida() const;
    bool compararFechas(const Fecha &inicio, const Fecha &fin) const;
    void mostrarDiaMes() const;
    Fecha sumarDias(int dias) const;
};

#endif
