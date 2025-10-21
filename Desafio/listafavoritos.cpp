#include "listafavoritos.h"
#include <iostream>

using namespace std;

static const int MAX_CAP = 10000;


int ListaFavoritos::indiceDeCancion(int id) const {
    for (int i = 0; i < cantidad; ++i) {
        if (canciones[i] == id) return i;
    }
    return -1;
}


ListaFavoritos::ListaFavoritos(const string& propietario, const string& nombre)
    : propietarioNick(propietario), nombreLista(nombre),
    capacidad(MAX_CAP), cantidad(0),
    agregadasPorSeguir(nullptr), cantidadAgregadasPorSeguir(0),
    siguiendoA(""), estaSiguiendo(false)
{
    canciones = new int[capacidad];
    // inicializar (opcional)
    for (int i = 0; i < capacidad; ++i) canciones[i] = 0;
    // seed para rand (si no lo hizo main)
    srand((unsigned) time(nullptr));
}

ListaFavoritos::ListaFavoritos(const ListaFavoritos& otro)
    : propietarioNick(otro.propietarioNick), nombreLista(otro.nombreLista),
    capacidad(otro.capacidad), cantidad(otro.cantidad),
    agregadasPorSeguir(nullptr), cantidadAgregadasPorSeguir(0),
    siguiendoA(otro.siguiendoA), estaSiguiendo(otro.estaSiguiendo)
{
    canciones = new int[capacidad];
    for (int i = 0; i < cantidad; ++i) canciones[i] = otro.canciones[i];

    if (otro.cantidadAgregadasPorSeguir > 0) {
        cantidadAgregadasPorSeguir = otro.cantidadAgregadasPorSeguir;
        agregadasPorSeguir = new int[cantidadAgregadasPorSeguir];
        for (int i = 0; i < cantidadAgregadasPorSeguir; ++i)
            agregadasPorSeguir[i] = otro.agregadasPorSeguir[i];
    } else {
        agregadasPorSeguir = nullptr;
    }
}

ListaFavoritos& ListaFavoritos::operator=(const ListaFavoritos& otro) {
    if (this == &otro) return *this;
    delete[] canciones;
    delete[] agregadasPorSeguir;

    propietarioNick = otro.propietarioNick;
    nombreLista = otro.nombreLista;
    capacidad = otro.capacidad;
    cantidad = otro.cantidad;

    canciones = new int[capacidad];
    for (int i = 0; i < cantidad; ++i) canciones[i] = otro.canciones[i];

    if (otro.cantidadAgregadasPorSeguir > 0) {
        cantidadAgregadasPorSeguir = otro.cantidadAgregadasPorSeguir;
        agregadasPorSeguir = new int[cantidadAgregadasPorSeguir];
        for (int i = 0; i < cantidadAgregadasPorSeguir; ++i)
            agregadasPorSeguir[i] = otro.agregadasPorSeguir[i];
    } else {
        agregadasPorSeguir = nullptr;
        cantidadAgregadasPorSeguir = 0;
    }

    siguiendoA = otro.siguiendoA;
    estaSiguiendo = otro.estaSiguiendo;

    return *this;
}

string ListaFavoritos::getPropietario() const { return propietarioNick; }
int ListaFavoritos::getCantidad() const { return cantidad; }
int ListaFavoritos::getCancionEn(int indice) const {
    if (indice < 0 || indice >= cantidad) return -1;
    return canciones[indice];
}

