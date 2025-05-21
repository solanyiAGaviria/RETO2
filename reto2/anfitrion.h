/*#ifndef ANFITRION_H
#define ANFITRION_H

class anfitrion {
public:
    char documento[20];
    int antiguedad;
    float puntuacion;

    anfitrion() {}
    anfitrion(const char* doc, int ant, float punt) {
        strcpy(documento, doc);
        antiguedad = ant;
        puntuacion = punt;
    }
    void mostrarDatos() {
        std::cout << "Anfitrión: " << documento << ", Antigüedad: " << antiguedad << ", Puntuación: " << puntuacion << std::endl;
    }
};/*


#endif // ANFITRION_H
