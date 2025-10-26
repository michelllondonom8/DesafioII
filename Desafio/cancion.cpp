#include "cancion.h"
using namespace std;

Cancion::Cancion() {
    id = 0;
    titulo = "Sin título";
    duracion = 0;
    rutaBaja = "";
    rutaAlta = "";
    albumID = "";
    reproducciones = 0;
    album = nullptr;
}

Cancion::Cancion(int _id, const string& _titulo, int _duracion,
                 const string& _rutaBaja, const string& _rutaAlta, const string& _albumID) {
    id = _id;
    titulo = _titulo;
    duracion = _duracion;
    rutaBaja = _rutaBaja;
    rutaAlta = _rutaAlta;
    albumID = _albumID;
    reproducciones = 0;
    album = nullptr;
}

Cancion::Cancion(const Cancion& otra) {
    id = otra.id;
    titulo = otra.titulo;
    duracion = otra.duracion;
    rutaBaja = otra.rutaBaja;
    rutaAlta = otra.rutaAlta;
    albumID = otra.albumID;
    reproducciones = otra.reproducciones;
    album = otra.album;
}

Cancion& Cancion::operator=(const Cancion& otra) {
    if (this == &otra) return *this;
    id = otra.id;
    titulo = otra.titulo;
    duracion = otra.duracion;
    rutaBaja = otra.rutaBaja;
    rutaAlta = otra.rutaAlta;
    albumID = otra.albumID;
    reproducciones = otra.reproducciones;
    album = otra.album;
    return *this;
}

Cancion::~Cancion() {
}
void Cancion::sumarReproduccion() {
    reproducciones++;
}
int Cancion::getId() const { return id; }
string Cancion::getTitulo() const { return titulo; }
int Cancion::getDuracion() const { return duracion; }
long Cancion::getReproducciones() const { return reproducciones; }
string Cancion::getRutaAlta() const { return rutaAlta; }
string Cancion::getRutaBaja() const { return rutaBaja; }
string Cancion::getAlbumID() const { return albumID; }

void Cancion::setAlbum(Album* a) { album = a; }
Album* Cancion::getAlbum() const { return album; }
