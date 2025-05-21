#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "usuarios.h"
#include "alojamientos.h"
#include "reservas.h"
#include "anfitrion.h"
#include "fecha.h"
using namespace std;
/* funcion que se encarga de leer un archivo txt y cuenta la camtidad de lineas y retorna este numero para
 * guardar la memoria del arrego.
 * despues de eso, se hace un for que coje la info de ese arreglo, lo va separandp por comas y se crear el objeto
 * con el constructor
*/
int main(){
    /*string cedula;
    string contrasena;
    cout<<"ingrese su documento"<<endl;
    cin>>cedula;
    cout<<"ingrese su contraseña"<<end;
    cin>>contrasena;
    //verificacion
    //carga de base de datos
    string alojamientos="alojamiento.txt";
    string reservas="reservas.txt";
    string anfitriones="anfitriones.txt";
    string usuarios="alojamiento.txt";

    int contAlojamientos=cantlineas(alojamientos);


    cout<<contAlojamientos<<endl;*/

    const int MAX = 100;

int main() {
        usuarios listaUsuarios[MAX];
        int contadorUsuarios = 0;

        std::ifstream archivo("usuarios.txt");
        if (!archivo.is_open()) {
            std::cerr << "Error al abrir el archivo usuarios.txt\n";
            return 1;
        }

        std::string linea;
        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string doc, clave, tiempoStr, puntStr;

            std::getline(ss, doc, ',');
            std::getline(ss, clave, ',');
            std::getline(ss, tiempoStr, ',');
            std::getline(ss, puntStr, ',');

            usuarios u(doc.c_str(), clave.c_str(), std::stoi(tiempoStr), std::stof(puntStr));
            listaUsuarios[contadorUsuarios++] = u;
        }

        archivo.close();

        std::cout << "\nUsuarios cargados:\n";
        for (int i = 0; i < contadorUsuarios; ++i) {
            listaUsuarios[i].mostrarDatos();
        }

        return 0;
    }
