#include "listafavoritos.h"
#include <iostream>

using namespace std;

static const int MAX_CAP = 10000;


int ListaFavoritos::indiceDeCancion(int id) const {
    for (int i = 0; i < cantidad; ++i) {
        if (canciones[i] == id) return i;
    }
    return -1;
}


ListaFavoritos::ListaFavoritos(const string& propietario, const string& nombre)
    : propietarioNick(propietario), nombreLista(nombre),
    capacidad(MAX_CAP), cantidad(0),
    agregadasPorSeguir(nullptr), cantidadAgregadasPorSeguir(0),
    siguiendoA(""), estaSiguiendo(false)
{
    canciones = new int[capacidad];
    for (int i = 0; i < capacidad; ++i) canciones[i] = 0;
    srand((unsigned) time(nullptr));
}

ListaFavoritos::ListaFavoritos(const ListaFavoritos& otro)
    : propietarioNick(otro.propietarioNick), nombreLista(otro.nombreLista),
    capacidad(otro.capacidad), cantidad(otro.cantidad),
    agregadasPorSeguir(nullptr), cantidadAgregadasPorSeguir(0),
    siguiendoA(otro.siguiendoA), estaSiguiendo(otro.estaSiguiendo)
{
    canciones = new int[capacidad];
    for (int i = 0; i < cantidad; ++i) canciones[i] = otro.canciones[i];

    if (otro.cantidadAgregadasPorSeguir > 0) {
        cantidadAgregadasPorSeguir = otro.cantidadAgregadasPorSeguir;
        agregadasPorSeguir = new int[cantidadAgregadasPorSeguir];
        for (int i = 0; i < cantidadAgregadasPorSeguir; ++i)
            agregadasPorSeguir[i] = otro.agregadasPorSeguir[i];
    } else {
        agregadasPorSeguir = nullptr;
    }
}

ListaFavoritos& ListaFavoritos::operator=(const ListaFavoritos& otro) {
    if (this == &otro) return *this;
    delete[] canciones;
    delete[] agregadasPorSeguir;

    propietarioNick = otro.propietarioNick;
    nombreLista = otro.nombreLista;
    capacidad = otro.capacidad;
    cantidad = otro.cantidad;

    canciones = new int[capacidad];
    for (int i = 0; i < cantidad; ++i) canciones[i] = otro.canciones[i];

    if (otro.cantidadAgregadasPorSeguir > 0) {
        cantidadAgregadasPorSeguir = otro.cantidadAgregadasPorSeguir;
        agregadasPorSeguir = new int[cantidadAgregadasPorSeguir];
        for (int i = 0; i < cantidadAgregadasPorSeguir; ++i)
            agregadasPorSeguir[i] = otro.agregadasPorSeguir[i];
    } else {
        agregadasPorSeguir = nullptr;
        cantidadAgregadasPorSeguir = 0;
    }

    siguiendoA = otro.siguiendoA;
    estaSiguiendo = otro.estaSiguiendo;

    return *this;
}

string ListaFavoritos::getPropietario() const { return propietarioNick; }
int ListaFavoritos::getCantidad() const { return cantidad; }
int ListaFavoritos::getCancionEn(int indice) const {
    if (indice < 0 || indice >= cantidad) return -1;
    return canciones[indice];
}

bool ListaFavoritos::agregar(int idCancion) {
    if (idCancion <= 0) return false;
    if (cantidad >= capacidad) return false;
    if (indiceDeCancion(idCancion) != -1) return false;
    canciones[cantidad++] = idCancion;
    return true;
}

bool ListaFavoritos::eliminar(int idCancion) {
    int idx = indiceDeCancion(idCancion);
    if (idx == -1) return false;
    canciones[idx] = canciones[--cantidad];
    return true;
}

void ListaFavoritos::mezclar() {
    if (cantidad <= 1) return;
    for (int i = cantidad - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int tmp = canciones[i];
        canciones[i] = canciones[j];
        canciones[j] = tmp;
    }
}

void ListaFavoritos::ejecutarLista() {
    cout << "[Reproduciendo lista de " << propietarioNick << " - " << nombreLista << "]\n";
    int K = cantidad;
    if (K == 0) {
        cout << "(Lista vacía)\n";
        return;
    }
    for (int i = 0; i < K; ++i) {
        cout << "-> Reproduciendo canción con ID: " << canciones[i] << endl;
        cout << "   (ruta portada: album/portada.png)" << endl;
        cout << "   (ruta audio: audio/" << canciones[i] << "_320.ogg)" << endl;
        this_thread::sleep_for(chrono::seconds(3));
    }
    cout << "[Fin de la lista]\n";
}

void ListaFavoritos::ejecutarLista(bool aleatorio) {
    if (aleatorio) {
        mezclar();
    }
    ejecutarLista();
}

bool ListaFavoritos::seguirOtraLista(ListaFavoritos* otra) {
    if (otra == nullptr) return false;
    if (otra == this) return false;
    if (estaSiguiendo) {
        cout << "[!] Ya estás siguiendo a: " << siguiendoA << ". Debes dejar de seguir antes.\n";
        return false;
    }

    int nuevas = 0;
    int maxAgregar = otra->getCantidad();
    int *temp = new int[maxAgregar];
    for (int i = 0; i < otra->getCantidad(); ++i) {
        int id = otra->getCancionEn(i);
        if (indiceDeCancion(id) == -1) {
            if (cantidad + nuevas >= capacidad) break;
            temp[nuevas++] = id;
        }
    }

    if (nuevas == 0) {
        delete[] temp;
        cout << "[i] No se agregaron canciones (ya existían o no hay espacio).\n";
        return false;
    }

    if (agregadasPorSeguir != nullptr) {
        delete[] agregadasPorSeguir;
        agregadasPorSeguir = nullptr;
        cantidadAgregadasPorSeguir = 0;
    }

    agregadasPorSeguir = new int[nuevas];
    for (int i = 0; i < nuevas; ++i) {
        canciones[cantidad + i] = temp[i];
        agregadasPorSeguir[i] = temp[i];
    }
    cantidadAgregadasPorSeguir = nuevas;
    cantidad += nuevas;
    siguiendoA = otra->getPropietario();
    estaSiguiendo = true;

    delete[] temp;
    cout << "[✓] Ahora sigues la lista de " << siguiendoA << ". Se agregaron " << nuevas << " canciones.\n";
    return true;
}

bool ListaFavoritos::dejarDeSeguir() {
    if (!estaSiguiendo) {
        cout << "[!] No sigues a nadie actualmente.\n";
        return false;
    }
    for (int i = 0; i < cantidadAgregadasPorSeguir; ++i) {
        int id = agregadasPorSeguir[i];
        int idx = indiceDeCancion(id);
        if (idx != -1) {
            // quitar (mover último)
            canciones[idx] = canciones[--cantidad];
            // si movimos un id que también está en agregadasPorSeguir, su posición en agregadasPorSeguir no importa
        }
    }

    delete[] agregadasPorSeguir;
    agregadasPorSeguir = nullptr;
    cantidadAgregadasPorSeguir = 0;
    cout << "[✓] Has dejado de seguir a " << siguiendoA << ". Las canciones agregadas por seguir fueron eliminadas.\n";
    siguiendoA = "";
    estaSiguiendo = false;
    return true;
}

int ListaFavoritos::operator[](int indice) const {
    if (indice < 0 || indice >= cantidad) return -1;
    return canciones[indice];
}

bool ListaFavoritos::operator==(const ListaFavoritos& otro) const {
    return propietarioNick == otro.propietarioNick;
}
ListaFavoritos::~ListaFavoritos() {
    delete[] canciones;
    delete[] agregadasPorSeguir;
}
