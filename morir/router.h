#ifndef ROUTER_H
#define ROUTER_H

#include <vector>
#include <utility>

class Router {
public:
    Router(int id);
    int idRouter;
    std::vector<std::pair<Router*, int>> vecinos; // vecinos y costos
    int distancia;
    bool visitado;
    std::vector<Router*> rutaMasCorta;

    void nuevoVecino(Router* vecino, int costo);
    void confDistancia(int distancia);
    void reinicio();
    void actualizarRuta(std::vector<Router*> ruta);
};

void dijkstra(Router* fuente);

#endif
