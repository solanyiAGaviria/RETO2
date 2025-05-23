#ifndef RED_H
#define RED_H

#include "Router.h"
#include <unordered_map>
#include <vector>
#include <string>

class Red {
private:
    std::unordered_map<int, Router*> routers;

    int nombreAId(char nombre);
    char idANombre(int id);

public:
    ~Red();
    void agregarRouter(int id);
    void eliminarRouter(int id);
    void conectar(int id1, int id2, int costo);
    void cargarDesdeArchivo(const std::string& nombreArchivo);
    void calcularRutas();
    int obtenerCosto(int origenID, int destinoID);
    std::vector<int> obtenerRuta(int origenID, int destinoID);
    void mostrarTablaAbsoluta();
    void mostrarTablaRelativa();
};

#endif

