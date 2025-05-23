#include "Router.h"
#include <climits>
#include <queue>


Router::Router(int id)
    : idRouter(id), distancia(INT_MAX), visitado(false) {}

void Router::nuevoVecino(Router* vecino, int costo) {
    vecinos.emplace_back(vecino, costo);
}

void Router::confDistancia(int dist) {
    distancia = dist;
}

void Router::reinicio() {
    distancia = INT_MAX;
    visitado = false;
    rutaMasCorta.clear();
}

void Router::actualizarRuta(std::vector<Router*> ruta) {
    rutaMasCorta = std::move(ruta);
}

void dijkstra(Router* fuente) {
    fuente->confDistancia(0);
    fuente->rutaMasCorta.push_back(fuente);

    std::priority_queue<std::pair<int, Router*>> pq;
    pq.push({0, fuente});

    while (!pq.empty()) {
        Router* actual = pq.top().second;
        pq.pop();

        if (actual->visitado) continue;
        actual->visitado = true;

        for (auto& vec : actual->vecinos) {
            Router* sigRouter = vec.first;
            int costoBorde = vec.second;

            int nuevaDistancia = actual->distancia + costoBorde;
            if (nuevaDistancia < sigRouter->distancia) {
                sigRouter->confDistancia(nuevaDistancia);

                std::vector<Router*> nuevaRuta = actual->rutaMasCorta;
                nuevaRuta.push_back(sigRouter);
                sigRouter->actualizarRuta(nuevaRuta);

                pq.push({-nuevaDistancia, sigRouter});
            }
        }
    }
}
