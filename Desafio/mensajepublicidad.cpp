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
    cout << " [" << categoria << "] Prioridad " << prioridad << "x - " << mensaje << endl;
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

MensajePublicidad* MensajePublicidad::elegirAleatorio(MensajePublicidad* lista, int cantidad) {
    if (cantidad <= 0) return nullptr;
    srand(static_cast<unsigned>(time(NULL)));
    int indice = rand() % cantidad;
    return &lista[indice];
}

