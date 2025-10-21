#ifndef LISTAFAVORITOS_H
#define LISTAFAVORITOS_H

#include <string>
using namespace std;

class ListaFavoritos {
private:
    string propietarioNick;
    string nombreLista;

    int *canciones;
    int capacidad;
    int cantidad;

    int *agregadasPorSeguir;
    int cantidadAgregadasPorSeguir;
    string siguiendoA;
    bool estaSiguiendo;

    int indiceDeCancion(int id) const;

public:

    ListaFavoritos(const string& propietario, const string& nombre = "Favoritos");
    ListaFavoritos(const ListaFavoritos& otro);
    ListaFavoritos& operator=(const ListaFavoritos& otro);
    ~ListaFavoritos();

    string getPropietario() const;
    int getCantidad() const;
    int getCancionEn(int indice) const;

    bool agregar(int idCancion);
    bool eliminar(int idCancion);
    void mezclar();
    void ejecutarLista();
    void ejecutarLista(bool aleatorio);

    bool seguirOtraLista(ListaFavoritos* otra);
    bool dejarDeSeguir();

    int operator[](int indice) const;
    bool operator==(const ListaFavoritos& otro) const;
};


#endif // LISTAFAVORITOS_H
