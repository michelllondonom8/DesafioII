#ifndef COLABORADOR_H
#define COLABORADOR_H
#include <string>
#include <iostream>
using namespace std;

class Colaborador {
private:
    string nombre;
    string apellido;
    string codigoAfiliacion;
    string tipo;

public:

    Colaborador();
    Colaborador(const string& nom, const string& ape, const string& cod, const string& tipo);

    ~Colaborador();


    void mostrar() const;


    string getTipo() const;
};

#endif // COLABORADOR_H
