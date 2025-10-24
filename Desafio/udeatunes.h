// UdeATunes.h
#ifndef UDEATUNES_H
#define UDEATUNES_H

#include "Usuario.h"
#include "Artista.h"
#include "Album.h"
#include "Cancion.h"
#include "mensajepublicidad.h"

class UdeATunes {
private:
    Usuario** usuarios;
    Artista** artistas;
    Cancion** canciones;
    MensajePublicidad* publicidades;

    int capacidadUsuarios;
    int capacidadArtistas;
    int capacidadCanciones;
    int capacidadPublicidades;

    int totalUsuarios;
    int totalArtistas;
    int totalCanciones;
    int totalPublicidades;

    unsigned long iteraciones;
    unsigned long memoriaEstimadaBytes;

    int ultimoAnuncioId;

    // auxiliares para carga
    void asegurarCapacidadUsuarios();
    void asegurarCapacidadArtistas();
    void asegurarCapacidadCanciones();
    void asegurarCapacidadPublicidades();

    // util
    void mostrarInterfazReproduccion(Cancion* c, Artista* artista, Album* album, bool esPremium);

public:
    UdeATunes();
    ~UdeATunes();

    void inicializar();
    void reproducirAleatorio(int k);
    void cargarUsuariosDesdeArchivo(const char* ruta);
    void cargarPublicidadesDesdeArchivo(const char* ruta);
    void cargarCancionesDesdeArchivo(const char* ruta);
    void cargarArtistasDesdeArchivo(const char* ruta);
    void menuPrincipal();

    // métricas
    void sumarIteraciones(unsigned long n = 1) { iteraciones += n; }
    void sumarMemoria(size_t bytes) { memoriaEstimadaBytes += bytes; }
};

#endif
