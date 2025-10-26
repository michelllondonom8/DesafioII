#ifndef ARTISTA_H
#define ARTISTA_H

#include <iostream>
#include <string>
#include "album.h"

class Artista {
private:
    std::string nombre;
    std::string pais;

    Album** albumes;
    int totalAlbumes;
    int capacidad;

    void ampliarEspacio();

public:
    Artista();
    Artista(const std::string& _nombre, const std::string& _pais);
    ~Artista();

    bool agregarAlbum(Album* a);
    std::string getNombre() const;

};

#endif
