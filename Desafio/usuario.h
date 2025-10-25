#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include "listafavoritos.h"
class UdeATunes;
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
    Usuario(string nick, string tipo, string ciudadU, string paisU, string fecha);
    ~Usuario();

    string getNickname() const;
    string getMembresia() const;
    void setMembresia(string tipo);
    string getCiudad() const;
    string getPais() const;
    string getFechaInscripcion() const;
    ListaFavoritos* getLista() const { return lista; }

    void mostrarInfo() const;
    bool agregarFavorito(UdeATunes* sistema);
    bool quitarFavorito(UdeATunes* sistema);
    void ejecutarFavoritos(UdeATunes* sistema);
    void seguirLista(UdeATunes* sistema);

};


#endif // USUARIO_H
