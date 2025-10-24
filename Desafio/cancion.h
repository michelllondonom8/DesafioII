#ifndef CANCION_H
#define CANCION_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "colaborador.h"
using namespace std;

class Cancion {
private:
    int id;
    string titulo;
    int duracion;
    string rutaBaja;
    string rutaAlta;
    string albumID;
    long reproducciones;

    Colaborador** creditos;
    int numCreditos;
    int capacidad;

    void ampliarCreditos();

public:
    Cancion();
    Cancion(int _id, const string& _titulo, int _duracion,
            const string& _rutaBaja, const string& _rutaAlta, const string& _albumID);
    Cancion(const Cancion& otra);
    Cancion& operator=(const Cancion& otra);
    ~Cancion();

    void reproducir(bool esPremium);
    void sumarReproduccion();

    bool agregarCredito(Colaborador* c);
    bool eliminarCredito(int pos);

    int getId() const;
    string getTitulo() const;
    int getDuracion() const;
    long getReproducciones() const;
    string getRutaAlta() const;
    string getRutaBaja()const;
    string getAlbumID() const;
    int getNumCreditos() const;

    bool operator==(const Cancion& otra) const;
    friend ostream& operator<<(ostream& os, const Cancion& c);
};

#endif

