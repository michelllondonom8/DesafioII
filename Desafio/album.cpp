#include "album.h"
#define CAPACIDAD_INICIAL 3
using namespace std;

Album::Album() {
    nombre = "Sin nombre";
    genero = "Desconocido";
    anio = 0;
    totalCanciones = 0;
    capacidad = CAPACIDAD_INICIAL;
    canciones = new Cancion*[capacidad];
    artista = nullptr;
    for (int i = 0; i < capacidad; ++i)
        canciones[i] = nullptr;
}

Album::Album(const std::string& _id, const std::string& _idArtista, const std::string& _nombre,
             const std::string& _genero, const std::string& _fecha, int _duracion,
             const std::string& _sello, int _puntuacion, const std::string& _rutaPortada) {
    id = _id;
    idArtista = _idArtista;
    nombre = _nombre;
    genero = _genero;
    anio = stoi(_fecha.substr(0,4));
    rutaPortada = _rutaPortada;
    sello = _sello;
    puntuacion = _puntuacion;
    duracionTotalAlbum = _duracion;

    totalCanciones = 0;
    capacidad = CAPACIDAD_INICIAL;
    canciones = new Cancion*[capacidad];
    artista = nullptr;
    for (int i = 0; i < capacidad; ++i)
        canciones[i] = nullptr;
}


Album::~Album() {
    delete[] canciones;
}

void Album::ampliarEspacio() {
    int nuevaCapacidad = capacidad * 2;
    Cancion** nuevaLista = new Cancion*[nuevaCapacidad];
    for (int i = 0; i < totalCanciones; ++i)
        nuevaLista[i] = canciones[i];
    for (int i = totalCanciones; i < nuevaCapacidad; ++i)
        nuevaLista[i] = nullptr;

    delete[] canciones;
    canciones = nuevaLista;
    capacidad = nuevaCapacidad;
}

bool Album::agregarCancion(Cancion* c) {
    if (c == nullptr) return false;
    for (int i = 0; i < totalCanciones; ++i)
        if (canciones[i] == c) return false;

    if (totalCanciones >= capacidad)
        ampliarEspacio();

    canciones[totalCanciones] = c;
    totalCanciones++;
    return true;
}
