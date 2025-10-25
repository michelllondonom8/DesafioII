#ifndef ALBUM_H
#define ALBUM_H

#include <iostream>
#include <string>
#include "cancion.h"
class Artista;
using namespace std;

class Album {
private:
    string id;
    string idArtista;
    string rutaPortada;
    string nombre;
    string genero;
    int anio;
    string sello;
    int puntuacion;
    int duracionTotalAlbum;

    Cancion** canciones;
    int totalCanciones;
    int capacidad;

    Artista* artista;

    void ampliarEspacio();

public:
    Album();
    Album(const string& _id, const string& _idArtista, const string& _nombre,
          const string& _genero, const string& _fecha, int _duracion,
          const string& _sello, int _puntuacion, const string& _rutaPortada);
    ~Album();

    bool agregarCancion(Cancion* c);
    int duracionTotal() const;
    void mostrarAlbum() const;

    string getId() const { return id; }
    string getIdArtista() const { return idArtista; }
    string getNombre() const { return nombre; }
    int getTotalCanciones() const { return totalCanciones; }
    string getRutaPortada() const { return rutaPortada; }
    Cancion* getCancion(int i) const { return canciones[i]; }

    void setArtista(Artista* a) { artista = a; }
    Artista* getArtista() const { return artista; }
};

#endif
