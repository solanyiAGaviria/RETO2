#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>

class Usuarios {
private:
    std::string cedula;
    std::string clave;
    float calificacion;

public:
    Usuarios();
    Usuarios(const std::string& ced, const std::string& clv, float calif);

    static Usuarios* desdeLinea(const std::string& linea);  // Método que convierte una línea en objeto
    void mostrar() const;
};

#endif

