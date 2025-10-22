#include "cancion.h"

#define CAPACIDAD_INICIAL 3

void Cancion::ampliarCreditos() {
    int nuevaCap = (capacidad == 0) ? CAPACIDAD_INICIAL : capacidad * 2;
    Colaborador** nuevo = new Colaborador*[nuevaCap];
    for (int i = 0; i < numCreditos; ++i) nuevo[i] = creditos[i];
    for (int i = numCreditos; i < nuevaCap; ++i) nuevo[i] = nullptr;
    delete[] creditos;
    creditos = nuevo;
    capacidad = nuevaCap;
}

Cancion::Cancion() {
    id = 0;
    titulo = "Sin título";
    duracion = 0;
    rutaBaja = "";
    rutaAlta = "";
    reproducciones = 0;
    numCreditos = 0;
    capacidad = CAPACIDAD_INICIAL;
    creditos = new Colaborador*[capacidad];
    for (int i = 0; i < capacidad; ++i) creditos[i] = nullptr;
}

Cancion::Cancion(int _id, const string& _titulo, int _duracion,
                 const string& _rutaBaja, const string& _rutaAlta) {
    id = _id;
    titulo = _titulo;
    duracion = _duracion;
    rutaBaja = _rutaBaja;
    rutaAlta = _rutaAlta;
    reproducciones = 0;
    numCreditos = 0;
    capacidad = CAPACIDAD_INICIAL;
    creditos = new Colaborador*[capacidad];
    for (int i = 0; i < capacidad; ++i) creditos[i] = nullptr;
}

Cancion::Cancion(const Cancion& otra) {
    id = otra.id;
    titulo = otra.titulo;
    duracion = otra.duracion;
    rutaBaja = otra.rutaBaja;
    rutaAlta = otra.rutaAlta;
    reproducciones = otra.reproducciones;

    numCreditos = otra.numCreditos;
    capacidad = otra.capacidad;
    creditos = new Colaborador*[capacidad];
    for (int i = 0; i < numCreditos; ++i) creditos[i] = otra.creditos[i];
    for (int i = numCreditos; i < capacidad; ++i) creditos[i] = nullptr;
}

Cancion& Cancion::operator=(const Cancion& otra) {
    if (this == &otra) return *this;
    delete[] creditos;

    id = otra.id;
    titulo = otra.titulo;
    duracion = otra.duracion;
    rutaBaja = otra.rutaBaja;
    rutaAlta = otra.rutaAlta;
    reproducciones = otra.reproducciones;
    numCreditos = otra.numCreditos;
    capacidad = otra.capacidad;
    creditos = new Colaborador*[capacidad];
    for (int i = 0; i < numCreditos; ++i) creditos[i] = otra.creditos[i];
    for (int i = numCreditos; i < capacidad; ++i) creditos[i] = nullptr;
    return *this;
}

Cancion::~Cancion() {
    delete[] creditos;
}

void Cancion::reproducir(bool esPremium) {
    cout << "🎵 Reproduciendo: " << titulo << endl;
    cout << "Duración: " << duracion << " segundos" << endl;
    cout << "Calidad: " << (esPremium ? "320 kbps" : "128 kbps") << endl;
    cout << "Ruta: " << (esPremium ? rutaAlta : rutaBaja) << endl;

    if (numCreditos > 0) {
        cout << "Créditos: ";
        for (int i = 0; i < numCreditos; ++i) {
            cout << creditos[i]->getTipo();
            if (i < numCreditos - 1) cout << ", ";
        }
        cout << endl;
    }

    this_thread::sleep_for(chrono::seconds(3));
    sumarReproduccion();
}

void Cancion::sumarReproduccion() {
    reproducciones++;
}

bool Cancion::agregarCredito(Colaborador* c) {
    if (!c) return false;
    for (int i = 0; i < numCreditos; ++i)
        if (creditos[i] == c) return false;

    if (numCreditos >= capacidad) ampliarCreditos();
    creditos[numCreditos++] = c;
    return true;
}

bool Cancion::eliminarCredito(int pos) {
    if (pos < 0 || pos >= numCreditos) return false;
    for (int i = pos; i < numCreditos - 1; ++i)
        creditos[i] = creditos[i + 1];
    numCreditos--;
    return true;
}

int Cancion::getId() const { return id; }
string Cancion::getTitulo() const { return titulo; }
int Cancion::getDuracion() const { return duracion; }
long Cancion::getReproducciones() const { return reproducciones; }
int Cancion::getNumCreditos() const { return numCreditos; }

bool Cancion::operator==(const Cancion& otra) const {
    return id == otra.id;
}

ostream& operator<<(ostream& os, const Cancion& c) {
    os << "ID: " << c.id << " | " << c.titulo << " | Reproducciones: " << c.reproducciones;
    return os;
}

