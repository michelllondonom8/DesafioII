#ifndef ALBUM_H
#define ALBUM_H

#include <iostream>
#include <string>
#include "cancion.h"
using namespace std;

class Album {
private:
    string nombre;
    string genero;
    int anio;

    Cancion** canciones;
    int totalCanciones;
    int capacidad;

    void ampliarEspacio();

public:
    Album();
    Album(const string& _nombre, const string& _genero, int _anio);
    ~Album();

    bool agregarCancion(Cancion* c);
    int duracionTotal() const;
    void mostrarAlbum() const;

    string getNombre() const;
    int getTotalCanciones() const;
};

#endif
