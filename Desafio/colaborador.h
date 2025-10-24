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

    string getNombre() const { return nombre; }
    string getApellido() const { return apellido; }
    string getCodigo() const { return codigoAfiliacion; }
    string getTipo() const {return tipo;}
};

#endif // COLABORADOR_H
