
#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>

class Usuarios {
private:
    std::string documento;
    std::string clave;

public:
    std::string nombre;
    std::string tiempoPlataforma;
    std::string puntuacion;
    std::string id;

    Usuarios();
    Usuarios(const std::string& nombre, const std::string& documento, const std::string& clave,
            const std::string& tiempo, const std::string& puntuacion, const std::string& id);

    void mostrar() const;
};

#endif
