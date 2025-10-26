#ifndef ALBUM_H
#define ALBUM_H

#include <iostream>
#include <string>
#include "cancion.h"
class Artista;
class Album {
private:
    std::string id;
    std::string idArtista;
    std::string rutaPortada;
    std::string nombre;
    std::string genero;
    int anio;
    std::string sello;
    int puntuacion;
    int duracionTotalAlbum;

    Cancion** canciones;
    int totalCanciones;
    int capacidad;

    Artista* artista;

    void ampliarEspacio();

public:
    Album();
    Album(const std::string& _id, const std::string& _idArtista, const std::string& _nombre,
          const std::string& _genero, const std::string& _fecha, int _duracion,
          const std::string& _sello, int _puntuacion, const std::string& _rutaPortada);
    ~Album();

    bool agregarCancion(Cancion* c);
    std::string getIdArtista() const { return idArtista; }
    std::string getNombre() const { return nombre; }
    int getTotalCanciones() const { return totalCanciones; }
    std::string getRutaPortada() const { return rutaPortada; }

    void setArtista(Artista* a) { artista = a; }
    Artista* getArtista() const { return artista; }
};

#endif
