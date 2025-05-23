#include "Red.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <climits>
#include <algorithm>
#include <cctype>

using namespace std;

Red::~Red() {
    for (auto& par : routers) delete par.second;
}

void Red::agregarRouter(int id) {
    if (routers.find(id) == routers.end()) {
        routers[id] = new Router(id);
    }
}

void Red::eliminarRouter(int id) {
    if (routers.find(id) != routers.end()) {
        delete routers[id];
        routers.erase(id);
        for (auto& par : routers) {
            auto& vecinos = par.second->vecinos;
            vecinos.erase(remove_if(vecinos.begin(), vecinos.end(), [id](const pair<Router*, int>& p) {
                              return p.first->idRouter == id;
                          }), vecinos.end());
        }
    }
}

void Red::conectar(int id1, int id2, int costo) {
    agregarRouter(id1);
    agregarRouter(id2);
    routers[id1]->nuevoVecino(routers[id2], costo);
    routers[id2]->nuevoVecino(routers[id1], costo);
}

int Red::nombreAId(char nombre) {
    return toupper(nombre) - 'A';
}

char Red::idANombre(int id) {
    return static_cast<char>('A' + id);
}

void Red::cargarDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        char a, b;
        int costo;
        if (!(iss >> a >> b >> costo)) continue;
        int id1 = nombreAId(a);
        int id2 = nombreAId(b);
        conectar(id1, id2, costo);
    }
    archivo.close();
}

void Red::calcularRutas() {
    for (auto& par : routers) {
        for (auto& p : routers) p.second->reinicio();
        dijkstra(par.second);
    }
}

int Red::obtenerCosto(int origenID, int destinoID) {
    if (routers.find(destinoID) != routers.end()) {
        return routers[destinoID]->distancia;
    }
    return -1;
}

vector<int> Red::obtenerRuta(int origenID, int destinoID) {
    vector<int> ruta;
    if (routers.find(destinoID) == routers.end() || routers.find(origenID) == routers.end()) return ruta;

    Router* destino = routers[destinoID];
    Router* actual = destino;

    unordered_map<Router*, Router*> anteriores;
    for (auto& par : routers) par.second->reinicio();
    routers[origenID]->confDistancia(0);
    priority_queue<pair<int, Router*>> pq;
    pq.push({0, routers[origenID]});

    while (!pq.empty()) {
        Router* actual = pq.top().second;
        pq.pop();
        if (actual->visitado) continue;
        actual->visitado = true;

        for (auto& vec : actual->vecinos) {
            Router* vecino = vec.first;
            int costo = vec.second;
            int nuevaDist = actual->distancia + costo;

            if (nuevaDist < vecino->distancia) {
                vecino->confDistancia(nuevaDist);
                anteriores[vecino] = actual;
                pq.push({-nuevaDist, vecino});
            }
        }
    }

    actual = destino;
    while (actual != routers[origenID]) {
        ruta.insert(ruta.begin(), actual->idRouter);
        if (anteriores.find(actual) == anteriores.end()) return {};
        actual = anteriores[actual];
    }
    ruta.insert(ruta.begin(), origenID);
    return ruta;
}

void Red::mostrarTablaAbsoluta() {
    cout << "\nTabla de Conectividad Absoluta:\n    ";
    for (const auto& col : routers) cout << idANombre(col.first) << "   ";
    cout << "\n";

    for (const auto& fila : routers) {
        cout << idANombre(fila.first) << " | ";
        for (const auto& col : routers) {
            if (fila.first == col.first) {
                cout << "0   ";
            } else {
                bool encontrado = false;
                for (const auto& v : fila.second->vecinos) {
                    if (v.first->idRouter == col.first) {
                        cout << v.second << "   ";
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) cout << "-   ";
            }
        }
        cout << "\n";
    }
}

void Red::mostrarTablaRelativa() {
    cout << "\nTabla de Rutas Minimas (Relativa):\n    ";
    for (const auto& col : routers) cout << idANombre(col.first) << "   ";
    cout << "\n";

    for (const auto& origen : routers) {
        for (auto& p : routers) p.second->reinicio();
        dijkstra(origen.second);

        cout << idANombre(origen.first) << " | ";
        for (const auto& destino : routers) {
            if (origen.first == destino.first) {
                cout << "0   ";
            } else if (destino.second->distancia == INT_MAX) {
                cout << "-   ";
            } else {
                cout << destino.second->distancia << "   ";
            }
        }
        cout << "\n";
    }
}
