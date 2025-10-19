#include "colaborador.h"
#include <iostream>
using namespace std;

Colaborador::Colaborador() {
    nombre = "";
    apellido = "";
    codigoAfiliacion = "";
    tipo = "";
}


Colaborador::Colaborador(const string& nom, const string& ape, const string& cod, const string& tipo) {
    this->nombre = nom;
    this->apellido = ape;
    this->codigoAfiliacion = cod;
    this->tipo = tipo;
}


Colaborador::~Colaborador() {}

void Colaborador::mostrar() const {
    cout << "Colaborador: " << nombre << " " << apellido
         << " | Código: " << codigoAfiliacion
         << " | Tipo: " << tipo << endl;
}

// Devuelve el tipo de colaborador
string Colaborador::getTipo() const {
    return tipo;
}
