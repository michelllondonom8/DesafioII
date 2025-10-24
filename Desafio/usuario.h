#ifndef USUARIO_H
#define USUARIO_H
#include <iostream>
#include <string>
#include "listafavoritos.h"
using namespace std;

class Usuario {
private:
    string nickname;
    string membresiaTipo; // "Premium" o "Estandar"
    string ciudad;
    string pais;
    string fechaInscripcion;
    ListaFavoritos* lista;

public:
    Usuario(string nick, string tipo, string ciudad, string pais, string fecha);
    ~Usuario();

    string getNickname() const;
    string getMembresia() const;
    void setMembresia(string tipo);
    string getCiudad() const;
    string getPais() const;
    string getFechaInscripcion() const;

    void mostrarInfo() const;
    bool agregarFavorito();
    bool quitarFavorito();
    void ejecutarFavoritos();
    void seguirLista();
};


#endif // USUARIO_H
