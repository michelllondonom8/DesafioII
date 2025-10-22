#ifndef MENSAJEPUBLICIDAD_H
#define MENSAJEPUBLICIDAD_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class MensajePublicidad {
private:
    int id;
    string mensaje;
    char categoria;
    int prioridad;

public:
    MensajePublicidad();
    MensajePublicidad(int _id, const string& _mensaje, char _categoria, int _prioridad = 1);
    ~MensajePublicidad();

    void mostrar() const;
    void cambiarCategoria(char tipo);

    int getPrioridad() const;
    int getId() const;
    string getMensaje() const;
    char getCategoria() const;

    static MensajePublicidad* elegirAleatorio(MensajePublicidad* lista, int cantidad);
};

#endif
