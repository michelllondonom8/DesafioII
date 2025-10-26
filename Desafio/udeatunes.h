#ifndef UDEATUNES_H
#define UDEATUNES_H
#include "Usuario.h"
#include "Artista.h"
#include "Album.h"
#include "Cancion.h"
#include "mensajepublicidad.h"
#include "listafavoritos.h"

class UdeATunes {
private:
    Usuario** usuarios;
    Artista** artistas;
    Cancion** canciones;
    Album** albumes;
    MensajePublicidad* publicidades;

    int totalUsuarios, totalArtistas, totalAlbumes, totalCanciones, totalPublicidades;
    int capacidadUsuarios, capacidadArtistas, capacidadAlbumes, capacidadCanciones, capacidadPublicidades;

    unsigned long iteraciones;
    unsigned long memoriaEstimadaBytes;

    int ultimoAnuncioId;

    void asegurarCapacidadUsuarios();
    void asegurarCapacidadArtistas();
    void asegurarCapacidadCanciones();
    void asegurarCapacidadPublicidades();
    void asegurarCapacidadAlbumes();

public:
    UdeATunes();
    ~UdeATunes();

    Cancion* buscarCancionPorId(int id);
    Cancion* buscarCancionPorNombre(const std::string& nombre);
    Usuario* buscarUsuario(const std::string& nickname);
    void inicializar();
    void reproducirAleatorio(int k, bool esPremium = false);
    void cargarAlbumesDesdeArchivo(const std::string& ruta);
    void cargarUsuariosDesdeArchivo(const char* ruta);
    void cargarPublicidadesDesdeArchivo(const char* ruta);
    void cargarCancionesDesdeArchivo(const std::string& ruta);
    void cargarArtistasDesdeArchivo(const char* ruta);
    void menuPrincipal();
    void cargarArchivos();

    // métricas
    void sumarIteraciones(unsigned long n = 1);
    void sumarMemoria(size_t bytes);
    void restarMemoria(size_t bytes);
    void mostrarEstadisticas() const;
    void menuPremium(Usuario* user);
    void menuEstandar(Usuario* user);
    void enlazarCancionesConAlbumesYArtistas();

};

#endif
