#include "artista.h"
using namespace std;
#define CAPACIDAD_INICIAL 3

Artista::Artista() {
    nombre = "Desconocido";
    pais = "N/A";
    totalAlbumes = 0;
    capacidad = CAPACIDAD_INICIAL;
    albumes = new Album*[capacidad];
    for (int i = 0; i < capacidad; ++i)
        albumes[i] = nullptr;
}

Artista::Artista(const string& _nombre, const string& _pais) {
    nombre = _nombre;
    pais = _pais;
    totalAlbumes = 0;
    capacidad = CAPACIDAD_INICIAL;
    albumes = new Album*[capacidad];
    for (int i = 0; i < capacidad; ++i)
        albumes[i] = nullptr;
}

Artista::~Artista() {
    delete[] albumes;
}

void Artista::ampliarEspacio() {
    int nuevaCapacidad = capacidad * 2;
    Album** nuevaLista = new Album*[nuevaCapacidad];
    for (int i = 0; i < totalAlbumes; ++i)
        nuevaLista[i] = albumes[i];
    for (int i = totalAlbumes; i < nuevaCapacidad; ++i)
        nuevaLista[i] = nullptr;

    delete[] albumes;
    albumes = nuevaLista;
    capacidad = nuevaCapacidad;
}

bool Artista::agregarAlbum(Album* a) {
    if (a == nullptr) return false;
    for (int i = 0; i < totalAlbumes; ++i)
        if (albumes[i] == a) return false;

    if (totalAlbumes >= capacidad)
        ampliarEspacio();

    albumes[totalAlbumes] = a;
    totalAlbumes++;
    return true;
}

string Artista::getNombre() const{
    return nombre;
}
