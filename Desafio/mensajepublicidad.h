#ifndef MENSAJEPUBLICIDAD_H
#define MENSAJEPUBLICIDAD_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class MensajePublicidad {
private:
    int id;
    std::string mensaje;
    char categoria;
    int prioridad;

public:
    MensajePublicidad();
    MensajePublicidad(int _id, const std::string& _mensaje, char _categoria, int _prioridad = 1);
    ~MensajePublicidad();


    int getPrioridad() const;
    int getId() const;
    std::string getMensaje() const;
    char getCategoria() const;
    static void inicializarAzar();
    static int elegirAleatorio(const MensajePublicidad* lista, int cantidad, int ultimoId);
};

#endif
