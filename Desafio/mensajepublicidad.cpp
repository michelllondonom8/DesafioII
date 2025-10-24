#include "mensajepublicidad.h"

MensajePublicidad::MensajePublicidad() {
    id = 0;
    mensaje = "Sin mensaje";
    categoria = 'C';
    prioridad = 1;
}

MensajePublicidad::MensajePublicidad(int _id, const string& _mensaje, char _categoria, int _prioridad) {
    id = _id;
    mensaje = _mensaje;
    categoria = _categoria;
    prioridad = _prioridad;
    cambiarCategoria(_categoria);
}

MensajePublicidad::~MensajePublicidad() {}

void MensajePublicidad::mostrar() const {
    cout << mensaje << endl;
    cout << "Categoría: " << categoria << endl;
}

void MensajePublicidad::cambiarCategoria(char tipo) {
    categoria = tipo;
    switch (tipo) {
    case 'C': prioridad = 1; break;
    case 'B': prioridad = 2; break;
    case 'A': prioridad = 3; break;
    default:
        categoria = 'C';
        prioridad = 1;
        break;
    }
}

int MensajePublicidad::getPrioridad() const { return prioridad; }
int MensajePublicidad::getId() const { return id; }
string MensajePublicidad::getMensaje() const { return mensaje; }
char MensajePublicidad::getCategoria() const { return categoria; }

void MensajePublicidad::inicializarAzar() {
    srand(static_cast<unsigned>(time(nullptr)));
}

int MensajePublicidad::elegirAleatorio(const MensajePublicidad* lista, int cantidad, int ultimoId) {
    if (cantidad <= 0 || lista == nullptr) return -1;
    int suma = 0;
    for (int i = 0; i < cantidad; ++i) suma += lista[i].getPrioridad();
    if (suma <= 0) return rand() % cantidad;

    const int MAX_INTENTOS = 8;
    for (int intento = 0; intento < MAX_INTENTOS; ++intento) {
        int r = (rand() % suma) + 1;
        int acumulado = 0;
        for (int i = 0; i < cantidad; ++i) {
            acumulado += lista[i].getPrioridad();
            if (r <= acumulado) {
                if (lista[i].getId() == ultimoId && cantidad > 1) {
                    break;
                }
                return i;
            }
        }
    }
    int r = (rand() % suma) + 1;
    int acumulado = 0;
    for (int i = 0; i < cantidad; ++i) {
        acumulado += lista[i].getPrioridad();
        if (r <= acumulado) return i;
    }
    return 0;
}
