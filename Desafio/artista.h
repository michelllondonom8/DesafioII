#ifndef ARTISTA_H
#define ARTISTA_H

#include <iostream>
#include <string>
#include "album.h"
using namespace std;

class Artista {
private:
    string nombre;
    string pais;

    Album** albumes;
    int totalAlbumes;
    int capacidad;

    void ampliarEspacio();

public:
    Artista();
    Artista(const string& _nombre, const string& _pais);
    ~Artista();

    bool agregarAlbum(Album* a);
    int contarCanciones() const;
    void mostrarArtista() const;

    string getNombre() const;
    int getTotalAlbumes() const;
};

#endif
