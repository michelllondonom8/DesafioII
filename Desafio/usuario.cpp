#include "Usuario.h"
#include <iostream>
using namespace std;

Usuario::Usuario(string nick, string tipo, string ciudadU, string paisU, string fecha)
    : nickname(nick), membresiaTipo(tipo), ciudad(ciudadU), pais(paisU), fechaInscripcion(fecha) {}

string Usuario::getNickname() const {
    return nickname;
}

string Usuario::getMembresia() const {
    return membresiaTipo;
}

void Usuario::setMembresia(string tipo) {
    membresiaTipo = tipo;
}

string Usuario::getCiudad() const {
    return ciudad;
}

string Usuario::getPais() const {
    return pais;
}

string Usuario::getFechaInscripcion() const {
    return fechaInscripcion;
}

// Mostrar la información del usuario
void Usuario::mostrarInfo() const {
    cout << "------------------------------------------" << endl;
    cout << "Nickname: " << nickname << endl;
    cout << "Tipo de membresía: " << membresiaTipo << endl;
    cout << "Ciudad: " << ciudad << endl;
    cout << "País: " << pais << endl;
    cout << "Fecha de inscripción: " << fechaInscripcion << endl;
    cout << "------------------------------------------" << endl;
}

bool Usuario::agregarFavorito() {
    if (membresiaTipo == "Premium") {
        cout << "[+] Canción agregada a lista de favoritos." << endl;
        return true;
    } else {
        cout << "[x] Los usuarios estándar no pueden agregar canciones a favoritos." << endl;
        return false;
    }
}

bool Usuario::quitarFavorito() {
    if (membresiaTipo == "Premium") {
        cout << "[-] Canción eliminada de lista de favoritos." << endl;
        return true;
    } else {
        cout << "[x] Los usuarios estándar no pueden eliminar canciones de favoritos." << endl;
        return false;
    }
}
void Usuario::ejecutarFavoritos() {
    if (membresiaTipo == "Premium") {
        cout << "[♪] Reproduciendo lista de favoritos..." << endl;
        cout << "   (Simulación de reproducción aleatoria de canciones Premium)" << endl;
    } else {
        cout << "[x] Los usuarios estándar no tienen lista de favoritos para reproducir." << endl;
    }
}
void Usuario::seguirLista() {
    if (membresiaTipo == "Premium") {
        cout << "[✓] Siguiendo la lista de favoritos de otro usuario." << endl;
    } else {
        cout << "[x] Los usuarios estándar no pueden seguir listas de otros usuarios." << endl;
    }
}

