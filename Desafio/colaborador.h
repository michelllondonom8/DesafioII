#ifndef COLABORADOR_H
#define COLABORADOR_H
#include <string>
#include <iostream>

class Colaborador {
private:
    std::string nombre;
    std::string apellido;
    std::string codigoAfiliacion;
    std::string tipo;

public:

    Colaborador();
    Colaborador(const std::string& nom, const std::string& ape, const std::string& cod, const std::string& tipo);

    ~Colaborador();

    void mostrar() const;

    std::string getNombre() const { return nombre; }
    std::string getApellido() const { return apellido; }
    std::string getCodigo() const { return codigoAfiliacion; }
    std::string getTipo() const {return tipo;}
};

#endif // COLABORADOR_H
