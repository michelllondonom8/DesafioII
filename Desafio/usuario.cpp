#include "Usuario.h"
#include <iostream>
using namespace std;

Usuario::Usuario()
    : nickname(""), membresiaTipo("Estandar"), ciudad(""), pais(""), fechaInscripcion(""), lista(nullptr)
{}

Usuario::Usuario(string nick, string tipo, string ciudadU, string paisU, string fecha)
    : nickname(nick), membresiaTipo(tipo), ciudad(ciudadU), pais(paisU), fechaInscripcion(fecha), lista(nullptr)
{
    // si la membresía contiene "Premium" (mayúsc/minúsc tolerada) creamos lista
    string tmp = membresiaTipo;
    for (char &c: tmp) c = tolower(c);
    if (tmp.find("premium") != string::npos) {
        lista = new ListaFavoritos(nickname, "Favoritos de " + nickname);
    }
}

Usuario::~Usuario() {
    delete lista;
}

string Usuario::getNickname() const { return nickname; }
string Usuario::getMembresia() const { return membresiaTipo; }
void Usuario::setMembresia(string tipo) { membresiaTipo = tipo; }

string Usuario::getCiudad() const { return ciudad; }
string Usuario::getPais() const { return pais; }
string Usuario::getFechaInscripcion() const { return fechaInscripcion; }

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
    if (!lista) {
        cout << "[x] No tiene lista de favoritos (no es Premium)." << endl;
        return false;
    }
    // interfaz: pedir id por consola (puedes cambiar esto para pasar id desde UdeATunes)
    int id;
    cout << "Ingrese id de la canción a agregar: ";
    cin >> id;
    bool ok = lista->agregar(id);
    if (ok) cout << "[+] Canción agregada a lista de favoritos." << endl;
    else cout << "[x] No se pudo agregar (ya existe o lista llena)." << endl;
    return ok;
}

bool Usuario::quitarFavorito() {
    if (!lista) {
        cout << "[x] No tiene lista de favoritos (no es Premium)." << endl;
        return false;
    }
    int id;
    cout << "Ingrese id de la canción a eliminar: ";
    cin >> id;
    bool ok = lista->eliminar(id);
    if (ok) cout << "[-] Canción eliminada de lista de favoritos." << endl;
    else cout << "[x] No se pudo eliminar (no existe)." << endl;
    return ok;
}

void Usuario::ejecutarFavoritos() {
    if (!lista) {
        cout << "[x] Los usuarios estándar no tienen lista de favoritos para reproducir." << endl;
        return;
    }
    int modo;
    cout << "1) Orden original  2) Aleatorio\nElija modo: ";
    cin >> modo;
    if (modo == 2) lista->ejecutarLista(true);
    else lista->ejecutarLista(false);
}

void Usuario::seguirLista() {
    cout << "[Funcionalidad seguir lista se debe invocar desde UdeATunes con otra ListaFavoritos*]" << endl;
}
