#include "album.h"

#define CAPACIDAD_INICIAL 3

Album::Album() {
    nombre = "Sin nombre";
    genero = "Desconocido";
    anio = 0;
    totalCanciones = 0;
    capacidad = CAPACIDAD_INICIAL;
    canciones = new Cancion*[capacidad];
    for (int i = 0; i < capacidad; i = i + 1)
        canciones[i] = nullptr;
}

Album::Album(const string& _nombre, const string& _genero, int _anio) {
    nombre = _nombre;
    genero = _genero;
    anio = _anio;
    totalCanciones = 0;
    capacidad = CAPACIDAD_INICIAL;
    canciones = new Cancion*[capacidad];
    for (int i = 0; i < capacidad; i = i + 1)
        canciones[i] = nullptr;
}

Album::~Album() {
    delete[] canciones;
}

void Album::ampliarEspacio() {
    int nuevaCapacidad = capacidad * 2;
    Cancion** nuevaLista = new Cancion*[nuevaCapacidad];
    for (int i = 0; i < totalCanciones; i = i + 1)
        nuevaLista[i] = canciones[i];
    for (int i = totalCanciones; i < nuevaCapacidad; i = i + 1)
        nuevaLista[i] = nullptr;

    delete[] canciones;
    canciones = nuevaLista;
    capacidad = nuevaCapacidad;
}

bool Album::agregarCancion(Cancion* c) {
    if (c == nullptr) return false;
    for (int i = 0; i < totalCanciones; i = i + 1)
        if (canciones[i] == c) return false;

    if (totalCanciones >= capacidad)
        ampliarEspacio();

    canciones[totalCanciones] = c;
    totalCanciones = totalCanciones + 1;
    return true;
}

int Album::duracionTotal() const {
    int total = 0;
    for (int i = 0; i < totalCanciones; i = i + 1)
        total = total + canciones[i]->getDuracion();
    return total;
}

void Album::mostrarAlbum() const {
    cout << "\n Álbum: " << nombre << " (" << anio << ")" << endl;
    cout << "Género: " << genero << endl;
    cout << "Canciones: " << totalCanciones << endl;

    for (int i = 0; i < totalCanciones; i = i + 1)
        cout << "  - " << canciones[i]->getTitulo() << endl;

    cout << "Duración total: " << duracionTotal() << " segundos" << endl;
}

string Album::getNombre() const { return nombre; }
int Album::getTotalCanciones() const { return totalCanciones; }
