#ifndef LISTAFAVORITOS_H
#define LISTAFAVORITOS_H
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
class ListaFavoritos {
private:
    std::string propietarioNick;
    std::string nombreLista;

    int *canciones;
    int capacidad;
    int cantidad;

    int *agregadasPorSeguir;
    int cantidadAgregadasPorSeguir;
    std::string siguiendoA;
    bool estaSiguiendo;

    int indiceDeCancion(int id) const;

public:

    ListaFavoritos(const std::string& propietario, const std::string& nombre = "Favoritos");
    ListaFavoritos(const ListaFavoritos& otro);
    ListaFavoritos& operator=(const ListaFavoritos& otro);
    ~ListaFavoritos();

    std::string getPropietario() const;
    int getCantidad() const;
    int getCancionEn(int indice) const;

    bool agregar(int idCancion);
    bool eliminar(int idCancion);
    void mezclar();
    bool seguirOtraLista(ListaFavoritos* otra);
    bool dejarDeSeguir();
    bool estaSiguiendoOtro();
};


#endif // LISTAFAVORITOS_H
