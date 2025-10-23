#include "artista.h"

#define CAPACIDAD_INICIAL 3

Artista::Artista() {
    nombre = "Desconocido";
    pais = "N/A";
    totalAlbumes = 0;
    capacidad = CAPACIDAD_INICIAL;
    albumes = new Album*[capacidad];
    for (int i = 0; i < capacidad; i = i + 1)
        albumes[i] = nullptr;
}

Artista::Artista(const string& _nombre, const string& _pais) {
    nombre = _nombre;
    pais = _pais;
    totalAlbumes = 0;
    capacidad = CAPACIDAD_INICIAL;
    albumes = new Album*[capacidad];
    for (int i = 0; i < capacidad; i = i + 1)
        albumes[i] = nullptr;
}

Artista::~Artista() {
    delete[] albumes;
}

void Artista::ampliarEspacio() {
    int nuevaCapacidad = capacidad * 2;
    Album** nuevaLista = new Album*[nuevaCapacidad];
    for (int i = 0; i < totalAlbumes; i = i + 1)
        nuevaLista[i] = albumes[i];
    for (int i = totalAlbumes; i < nuevaCapacidad; i = i + 1)
        nuevaLista[i] = nullptr;

    delete[] albumes;
    albumes = nuevaLista;
    capacidad = nuevaCapacidad;
}

bool Artista::agregarAlbum(Album* a) {
    if (a == nullptr) return false;
    for (int i = 0; i < totalAlbumes; i = i + 1)
        if (albumes[i] == a) return false;

    if (totalAlbumes >= capacidad)
        ampliarEspacio();

    albumes[totalAlbumes] = a;
    totalAlbumes = totalAlbumes + 1;
    return true;
}

int Artista::contarCanciones() const {
    int total = 0;
    for (int i = 0; i < totalAlbumes; i = i + 1)
        total = total + albumes[i]->getTotalCanciones();
    return total;
}

void Artista::mostrarArtista() const {
    cout << "\n🎤 Artista: " << nombre << " (" << pais << ")" << endl;
    cout << "Álbumes: " << totalAlbumes << " | Total de canciones: " << contarCanciones() << endl;

    for (int i = 0; i < totalAlbumes; i = i + 1)
        albumes[i]->mostrarAlbum();
}

string Artista::getNombre() const { return nombre; }
int Artista::getTotalAlbumes() const { return totalAlbumes; }
