// CargaDatos.cpp
#include "CargaDatos.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

CargaDatos::CargaDatos() {
    alojamientos = new Alojamiento*[MAX_ALOJAMIENTOS];
    anfitriones = new Anfitrion*[MAX_ANFITRIONES];
    usuarios = new Usuario*[MAX_USUARIOS];
    reservas = new Reservacion*[MAX_RESERVAS];
    totalAlojamientos = totalAnfitriones = totalUsuarios = totalReservas = 0;
}

CargaDatos::~CargaDatos() {
    delete[] alojamientos;
    delete[] anfitriones;
    delete[] usuarios;
    delete[] reservas;
}

Alojamiento** CargaDatos::getAlojamientos() { return alojamientos; }
int CargaDatos::getTotalAlojamientos() const { return totalAlojamientos; }

Anfitrion** CargaDatos::getAnfitriones() { return anfitriones; }
int CargaDatos::getTotalAnfitriones() const { return totalAnfitriones; }

Usuario** CargaDatos::getUsuarios() { return usuarios; }
int CargaDatos::getTotalUsuarios() const { return totalUsuarios; }

Reservacion** CargaDatos::getReservas() { return reservas; }
int CargaDatos::getTotalReservas() const { return totalReservas; }

void CargaDatos::cargarAlojamientos(const string& ruta) {
    ifstream file(ruta);
    if (!file.is_open()) {
        cerr << "No se pudo abrir archivo de alojamientos\n";
        return;
    }

    string linea;
    getline(file, linea);

    while (getline(file, linea)) {
        stringstream ss(linea);
        string token;

        int id, precio;
        string nombre, dep, mun, tipo, dir, amen;

        getline(ss, token, ';'); id = stoi(token);
        getline(ss, nombre, ';');
        getline(ss, dep, ';');
        getline(ss, mun, ';');
        getline(ss, tipo, ';');
        getline(ss, dir, ';');
        getline(ss, token, ';'); precio = stoi(token);
        getline(ss, amen);

        alojamientos[totalAlojamientos++] = new Alojamiento(id, nombre, dep, mun, tipo, dir, precio, amen);
    }
    file.close();
}

void CargaDatos::cargarAnfitriones(const string& ruta) {
    ifstream file(ruta);
    if (!file.is_open()) {
        cerr << "No se pudo abrir archivo de anfitriones\n";
        return;
    }

    string linea;
    getline(file, linea);

    while (getline(file, linea)) {
        stringstream ss(linea);
        string token;

        long cedula;
        string nombre, clave, alojamientos_str;
        int antiguedad;
        float calificacion;

        getline(ss, token, ';'); cedula = stol(token);
        getline(ss, nombre, ';');
        getline(ss, clave, ';');
        getline(ss, token, ';'); antiguedad = stoi(token);
        getline(ss, token, ';'); calificacion = stof(token);
        getline(ss, alojamientos_str);

        Anfitrion* anfitrion = new Anfitrion(cedula, nombre, clave, antiguedad, calificacion);

        stringstream alojamientos_ss(alojamientos_str);
        while (getline(alojamientos_ss, token, ',')) {
            int id = stoi(token);
            Alojamiento* aloja = buscarAlojamientoPorId(id);
            if (aloja) {
                aloja->setAnfitrion(anfitrion);
                anfitrion->añadirAlojamiento(aloja);
            }
        }

        anfitriones[totalAnfitriones++] = anfitrion;
    }
    file.close();
}

void CargaDatos::cargarUsuarios(const string& ruta) {
    ifstream file(ruta);
    if (!file.is_open()) {
        cerr << "No se pudo abrir archivo de usuarios\n";
        return;
    }

    string linea;
    getline(file, linea);

    while (getline(file, linea)) {
        stringstream ss(linea);
        string token;

        long cedula;
        string nombre, clave;
        float calificacion;

        getline(ss, token, ';'); cedula = stol(token);
        getline(ss, nombre, ';');
        getline(ss, clave, ';');
        getline(ss, token); calificacion = stof(token);

        usuarios[totalUsuarios++] = new Usuario(cedula, nombre, clave, calificacion);
    }
    file.close();
}

void CargaDatos::cargarReservaciones(const string& ruta) {
    ifstream file(ruta);
    if (!file.is_open()) {
        cerr << "No se pudo abrir archivo de reservaciones\n";
        return;
    }

    string linea;
    getline(file, linea);

    while (getline(file, linea)) {
        stringstream ss(linea);
        string token;

        string codigo, metodo_pago, pregunta;
        long cedula_usuario;
        int id_aloja;
        string fechaPagoStr, fechaIniStr, fechaFinStr;

        getline(ss, codigo, ';');
        getline(ss, token, ';'); cedula_usuario = stol(token);
        getline(ss, token, ';'); id_aloja = stoi(token);
        getline(ss, fechaPagoStr, ';');
        getline(ss, metodo_pago, ';');
        getline(ss, fechaIniStr, ';');
        getline(ss, fechaFinStr, ';');
        getline(ss, pregunta);

        int dp, mp, ap, di, mi, ai, df, mf, af;
        sscanf(fechaPagoStr.c_str(), "%d/%d/%d", &dp, &mp, &ap);
        sscanf(fechaIniStr.c_str(), "%d/%d/%d", &di, &mi, &ai);
        sscanf(fechaFinStr.c_str(), "%d/%d/%d", &df, &mf, &af);

        Fecha fecha_pago(dp, mp, ap);
        Fecha fecha_ini(di, mi, ai);
        Fecha fecha_fin(df, mf, af);

        Reservacion* reserva = new Reservacion(codigo, cedula_usuario, id_aloja,
                                               fecha_pago, metodo_pago, fecha_ini, fecha_fin, pregunta);

        Alojamiento* aloja = buscarAlojamientoPorId(id_aloja);
        Usuario* usuario = buscarUsuarioPorCedula(cedula_usuario);

        if (aloja) aloja->añadirReserva(reserva);
        if (usuario) usuario->añadirReserva(reserva);


        reservas[totalReservas++] = reserva;
    }
    file.close();

    // Verificación cruzada, discutirlo con sol.
    for (int i = 0; i < totalAlojamientos; i++) {
        if (!alojamientos[i]->getAnfitrion()) {
            cerr << "Advertencia: El alojamiento ID " << alojamientos[i]->getId()
            << " no tiene anfitrión asignado.\n";
        }
    }

    for (int i = 0; i < totalReservas; i++) {
        Usuario* u = buscarUsuarioPorCedula(reservas[i]->getCedulaUsuario());
        Alojamiento* a = buscarAlojamientoPorId(reservas[i]->getIdAlojamiento());
        if (!u || !a) {
            cerr << "Advertencia: La reserva " << reservas[i]->getCodigo()
            << " no tiene usuario o alojamiento válido.\n";
        }
    }
}

Alojamiento* CargaDatos::buscarAlojamientoPorId(int id) {
    int izquierda = 0;
    int derecha = totalAlojamientos - 1;

    while (izquierda <= derecha) {
        int medio = (izquierda + derecha) / 2;
        int idActual = alojamientos[medio]->getId();

        if (idActual == id)
            return alojamientos[medio];
        else if (idActual < id)
            izquierda = medio + 1;
        else
            derecha = medio - 1;
    }
    return nullptr; // No encontrado
}

Usuario* CargaDatos::buscarUsuarioPorCedula(int cedula) {
    int izquierda = 0;
    int derecha = totalUsuarios - 1;

    while (izquierda <= derecha) {
        int medio = (izquierda + derecha) / 2;
        int cedActual = usuarios[medio]->getCedula();

        if (cedActual == cedula)
            return usuarios[medio];
        else if (cedActual < cedula)
            izquierda = medio + 1;
        else
            derecha = medio - 1;
    }
    return nullptr; // No encontrado
}

Anfitrion* CargaDatos::buscarAnfitrionPorCedula(int cedula) {
    int izquierda = 0;
    int derecha = totalAnfitriones - 1;
    while (izquierda <= derecha) {
        int medio = (izquierda + derecha) / 2;
        int cedActual = anfitriones[medio]->getCedula();

        if (cedActual == cedula)
            return anfitriones[medio];
        else if (cedActual < cedula)
            izquierda = medio + 1;
        else
            derecha = medio - 1;
    }
    return nullptr; // No encontrado
}

void CargaDatos::incrementarTotalReservas() {
    totalReservas++;
}

void CargaDatos::reservarPorCodigo(Usuario* usuario) {
    int id;
    cout << "Ingrese el ID del alojamiento: ";
    cin >> id;

    Alojamiento* alojamiento = buscarAlojamientoPorId(id);
    if (!alojamiento) {
        cout << "Alojamiento no encontrado.\n";
        return;
    }

    alojamiento->mostrarAlojamiento();

    Fecha hoy = Fecha::fechaActual(); // Asegúrate de tener este método implementado
    alojamiento->fechasDisponibles(hoy);

    // Validar fecha de inicio y disponibilidad
    Fecha inicio, fin;
    int noches;
    bool fechaOk = false;

    do {
        cout << "Ingrese la fecha de inicio (dd mm aaaa): ";
        int d, m, a;
        cin >> d >> m >> a;
        inicio = Fecha(d, m, a);

        if (!inicio.fechaValida()) {
            cout << "Fecha invalida. Intente nuevamente.\n";
            continue;
        }

        cout << "Cantidad de noches: ";
        cin >> noches;
        if (noches < 1) {
            cout << "Debe reservar al menos una noche.\n";
            continue;
        }

        fin = inicio.sumarDias(noches - 1);

        // Validar disponibilidad
        bool disponible = true;
        for (int i = 0; i < noches; i++) {
            Fecha f = inicio.sumarDias(i);
            if (!alojamiento->estaDisponible(f, hoy)) {
                disponible = false;
                break;
            }
        }

        if (!disponible) {
            cout << "El rango de fechas no esta completamente disponible. Intente con otra fecha.\n";
        } else {
            fechaOk = true;
        }

    } while (!fechaOk);

    // Método de pago
    string metodo;
    int metodoOpcion;
    do {
        cout << "Método de pago (1 = PSE, 2 = TCredito): ";
        cin >> metodoOpcion;
        if (metodoOpcion == 1) metodo = "PSE";
        else if (metodoOpcion == 2) metodo = "TCredito";
        else cout << "Opción inválida.\n";
    } while (metodoOpcion != 1 && metodoOpcion != 2);

    // Fecha de pago validada
    Fecha pago;
    bool pagoOk = false;
    do {
        cout << "Fecha de pago (dd mm aaaa): ";
        int d, m, a;
        cin >> d >> m >> a;
        pago = Fecha(d, m, a);

        if (!pago.fechaValida()) {
            cout << "Fecha de pago inválida. Intente nuevamente.\n";
        } else {
            pagoOk = true;
        }
    } while (!pagoOk);

    // Crear y registrar la reservación
    stringstream ss;
    ss << "RSV" << setfill('0') << setw(4) << totalReservas + 1;
    string codigo = ss.str();

    Reservacion* r = new Reservacion(codigo, usuario->getCedula(), id, pago, metodo, inicio, fin, "");
    usuario->añadirReserva(r);
    alojamiento->añadirReserva(r);
    reservas[totalReservas++] = r;

    cout << "\nReservacion creada exitosamente:\n";
    r->mostrarComprobante();
}


void CargaDatos::anularReserva(Usuario* usuario) {
    cout << "Ingrese el código de la reservación que desea anular: ";
    string codigo;
    cin >> codigo;

    for (int i = 0; i < totalReservas; i++) {
        if (reservas[i] && reservas[i]->getCodigo() == codigo && reservas[i]->getCedulaUsuario() == usuario->getCedula()) {
            int idAloj = reservas[i]->getIdAlojamiento();
            Alojamiento* aloja = buscarAlojamientoPorId(idAloj);
            if (aloja) aloja->quitarReserva(codigo);
            usuario->quitarReserva(codigo);
            delete reservas[i];
            reservas[i] = new Reservacion("GENERIC");
            cout << "Reservación anulada correctamente.\n";
            return;
        }
    }
    cout << "No se encontró una reservación válida con ese código.\n";
}

void CargaDatos::reservarConFiltros(Usuario* usuario) {
    string municipio;
    int d, m, a;
    int noches;
    int precioMax = 150000;  // valor por defecto
    float califMin = 0.0;    // sin filtro si queda en cero

    cout << "Ingrese el municipio deseado: ";
    cin.ignore(); // Limpiar buffer
    getline(cin, municipio);

    cout << "Ingrese la fecha de inicio (dd mm aaaa): ";
    cin >> d >> m >> a;
    Fecha fechaInicio(d, m, a);

    cout << "Cantidad de noches: ";
    cin >> noches;

    char usarPrecio, usarCalif;
    cout << "Desea filtrar por precio maximo? (s/n): ";
    cin >> usarPrecio;
    if (usarPrecio == 's' || usarPrecio == 'S') {
        cout << "Ingrese el precio maximo por noche (entre 25000 y 150000): ";
        cin >> precioMax;
    }

    cout << "Desea filtrar por calificacion minima del anfitrion? (s/n): ";
    cin >> usarCalif;
    if (usarCalif == 's' || usarCalif == 'S') {
        cout << "Ingrese la calificacion minima del anfitrion: ";
        cin >> califMin;
    }

    // Mostrar alojamientos que cumplen los filtros
    cout << "\n--- Resultados encontrados ---\n";
    int coincidencias = 0;
    Alojamiento* candidatos[MAX_ALOJAMIENTOS];

    for (int i = 0; i < totalAlojamientos; i++) {
        Alojamiento* alo = alojamientos[i];
        Anfitrion* anf = alo->getAnfitrion();

        if (alo->getMunicipio() != municipio) continue;
        if (alo->getPrecioNoche() > precioMax) continue;
        if (anf && anf->getCalificacion() < califMin) continue;

        cout << "\nOpción #" << (coincidencias + 1) << ":\n";
        alo->mostrarAlojamiento();
        candidatos[coincidencias++] = alo;
    }

    if (coincidencias == 0) {
        cout << "No se encontraron alojamientos con los filtros seleccionados.\n";
        return;
    }

    int opcion;
    do {
        cout << "\nSeleccione el número del alojamiento a reservar (1-" << coincidencias << "): ";
        cin >> opcion;
    } while (opcion < 1 || opcion > coincidencias);

    Alojamiento* seleccionado = candidatos[opcion - 1];

    // Método de pago
    string metodo;
    int metodoOpcion;
    do {
        cout << "Método de pago (1 = PSE, 2 = TCredito): ";
        cin >> metodoOpcion;
        if (metodoOpcion == 1) metodo = "PSE";
        else if (metodoOpcion == 2) metodo = "TCredito";
        else cout << "Opción inválida.\n";
    } while (metodoOpcion != 1 && metodoOpcion != 2);

    // Fecha de pago
    Fecha fechaPago;
    cout << "Ingrese la fecha de pago (dd mm aaaa): ";
    cin >> d >> m >> a;
    fechaPago = Fecha(d, m, a);

    Fecha fechaFin = fechaInicio.sumarDias(noches);

    stringstream ss;
    ss << "RSV" << setfill('0') << setw(4) << totalReservas + 1;
    string codigo = ss.str();

    Reservacion* r = new Reservacion(codigo, usuario->getCedula(), seleccionado->getId(), fechaPago, metodo, fechaInicio, fechaFin, "");
    usuario->añadirReserva(r);
    seleccionado->añadirReserva(r);
    reservas[totalReservas] = r;
    incrementarTotalReservas();

    cout << "\nReservación realizada con éxito:\n";
    r->mostrarComprobante();
}

// Funcionalidades del menu de anfitrion
void CargaDatos::consultarReservacionesAnfitrion(Anfitrion* anfitrion) {
    cout << "\n--- Consultar reservaciones ---\n";

    Fecha hoy = Fecha::fechaActual();
    Fecha inicio, fin;
    bool rangoValido = false;

    do {
        cout << "Ingrese la fecha de inicio del rango (dd mm aaaa): ";
        int d, m, a;
        cin >> d >> m >> a;
        inicio = Fecha(d, m, a);
        if (!inicio.fechaValida()) {
            cout << "Fecha de inicio invalida.\n";
            continue;
        }
        if (inicio < hoy) {
            cout << "La fecha de inicio no puede ser menor a hoy.\n";
            continue;
        }

        cout << "Ingrese la fecha final del rango (dd mm aaaa): ";
        cin >> d >> m >> a;
        fin = Fecha(d, m, a);
        if (!fin.fechaValida()) {
            cout << "Fecha final invalida.\n";
            continue;
        }
        if (fin < inicio) {
            cout << "La fecha final no puede ser menor que la de inicio.\n";
            continue;
        }

        rangoValido = true;
    } while (!rangoValido);

    // Recorremos alojamientos del anfitrion
    bool hayReservas = false;
    for (int i = 0; i < anfitrion->getCantidadAlojamientos(); i++) {
        Alojamiento* aloja = anfitrion->getAlojamiento(i);
        if (!aloja) continue;

        cout << "\nAlojamiento: " << aloja->getNombre() << " (ID: " << aloja->getId() << ")\n";

        bool alojaTiene = false;
        for (int j = 0; j < aloja->getCantidadReservas(); j++) {
            Reservacion* r = aloja->getReserva(j);
            if (r && !r->esGenerica()) {
                Fecha iniR = r->getFechaInicio();
                Fecha finR = r->getFechaFin();

                // Verificar si se traslapan con el rango solicitado
                if ((iniR <= fin && finR >= inicio)) {
                    cout << "- Codigo: " << r->getCodigo() << "\n";
                    cout << "  Inicio: "; iniR.mostrarDiaMes();
                    cout << "  Fin: ";    finR.mostrarDiaMes();
                    cout << endl;
                    alojaTiene = true;
                    hayReservas = true;
                }
            }
        }

        if (!alojaTiene) {
            cout << "  No hay reservaciones en el rango seleccionado.\n";
        }
    }

    if (!hayReservas) {
        cout << "\nNo se encontraron reservaciones para ningun alojamiento en el rango seleccionado.\n";
    }
}


void CargaDatos::eliminarReservacionAnfitrion(Anfitrion* anfitrion) {
    cout << "\n--- Eliminar reservacion ---\n";
    cout << "Ingrese el codigo de la reservacion a eliminar: ";
    string codigo;
    cin >> codigo;

    // Buscar la reserva
    Reservacion* reserva = nullptr;
    int index = -1;
    for (int i = 0; i < totalReservas; i++) {
        if (reservas[i] && reservas[i]->getCodigo() == codigo && !reservas[i]->esGenerica()) {
            reserva = reservas[i];
            index = i;
            break;
        }
    }

    if (!reserva) {
        cout << "No se encontro una reservacion con ese codigo.\n";
        return;
    }

    // Verificar si el anfitrion tiene ese alojamiento
    int idAloj = reserva->getIdAlojamiento();
    Alojamiento* aloja = buscarAlojamientoPorId(idAloj);

    bool pertenece = false;
    for (int i = 0; i < anfitrion->getCantidadAlojamientos(); i++) {
        if (anfitrion->getAlojamiento(i)->getId() == idAloj) {
            pertenece = true;
            break;
        }
    }

    if (!pertenece || !aloja) {
        cout << "La reservacion no pertenece a ninguno de sus alojamientos.\n";
        return;
    }

    // Buscar el usuario para quitarle la reserva
    Usuario* usuario = buscarUsuarioPorCedula(reserva->getCedulaUsuario());
    if (usuario) usuario->quitarReserva(codigo);
    aloja->quitarReserva(codigo);

    delete reservas[index];
    reservas[index] = new Reservacion("GENERIC");

    cout << "Reservacion eliminada correctamente.\n";
}


void CargaDatos::actualizarHistorico(Anfitrion* anfitrion) {
    cout << "\n--- Actualizar historico ---\n";

    Fecha hoy = Fecha::fechaActual();
    Fecha corte;
    int d, m, a;

    // Solicitar y validar fecha de corte
    bool valida = false;
    do {
        cout << "Ingrese la fecha de corte (dd mm aaaa): ";
        cin >> d >> m >> a;
        corte = Fecha(d, m, a);

        if (!corte.fechaValida()) {
            cout << "Fecha invalida. Intente de nuevo.\n";
        } else if (corte < hoy) {
            cout << "La fecha de corte no puede ser menor al dia actual.\n";
        } else if (corte > hoy.sumarDias(364)) {
            cout << "La fecha de corte no puede superar 12 meses desde hoy.\n";
        } else {
            valida = true;
        }
    } while (!valida);

    ofstream out("historico.txt", ios::app);
    if (!out.is_open()) {
        cerr << "No se pudo abrir el archivo historico.txt\n";
        return;
    }

    int eliminadas = 0;

    // Recorrer alojamientos del anfitrion
    for (int i = 0; i < anfitrion->getCantidadAlojamientos(); i++) {
        Alojamiento* aloja = anfitrion->getAlojamiento(i);
        if (!aloja) continue;

        for (int j = 0; j < aloja->getCantidadReservas(); j++) {
            Reservacion* r = aloja->getReserva(j);
            if (!r || r->esGenerica()) continue;

            if (r->getFechaFin() < corte) {
                // Guardar en el archivo
                out << r->getCodigo() << ";"
                    << r->getCedulaUsuario() << ";"
                    << r->getIdAlojamiento() << ";"
                    << r->getFechaPago().toString() << ";"
                    << r->getMetodoPago() << ";"
                    << r->getFechaInicio().toString() << ";"
                    << r->getFechaFin().toString() << ";"
                    << r->getPregunta() << "\n";

                // Eliminar en usuario
                Usuario* usuario = buscarUsuarioPorCedula(r->getCedulaUsuario());
                if (usuario) usuario->quitarReserva(r->getCodigo());

                // Eliminar en alojamiento
                aloja->quitarReserva(r->getCodigo());

                // Eliminar en arreglo global
                for (int k = 0; k < totalReservas; k++) {
                    if (reservas[k] && reservas[k]->getCodigo() == r->getCodigo()) {
                        delete reservas[k];
                        reservas[k] = new Reservacion("GENERIC");
                        break;
                    }
                }

                eliminadas++;
            }
        }
    }

    out.close();

    cout << eliminadas << " reservacion(es) fueron archivadas correctamente.\n";
}


