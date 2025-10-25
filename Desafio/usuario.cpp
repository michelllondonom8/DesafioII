#include "Usuario.h"
#include <iostream>
using namespace std;
#include "udeatunes.h"
#include <thread>
#include <chrono>

Usuario::Usuario(string nick, string tipo, string ciudadU, string paisU, string fecha)
    : nickname(nick), membresiaTipo(tipo), ciudad(ciudadU), pais(paisU), fechaInscripcion(fecha) {
    if (membresiaTipo == "Premium") {
        lista = new ListaFavoritos(nickname, "Favoritos de " + nickname);
    } else {
        lista = nullptr;
    }
}

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
void Usuario::mostrarInfo() const {
    cout << "------------------------------------------" << endl;
    cout << "Nickname: " << nickname << endl;
    cout << "Tipo de membresía: " << membresiaTipo << endl;
    cout << "Ciudad: " << ciudad << endl;
    cout << "Pais: " << pais << endl;
    cout << "Fecha de inscripción: " << fechaInscripcion << endl;
    cout << "------------------------------------------" << endl;
}

bool Usuario::agregarFavorito(UdeATunes* sistema) {
    cout << "\n--- Agregar cancion a favoritos ---\n";
    cout << "Ingrese el nombre de la cancion: ";
    cin.ignore();
    string nombreCancion;
    getline(cin, nombreCancion);

    sistema->sumarIteraciones();
    Cancion* cancion = sistema->buscarCancionPorNombre(nombreCancion);

    if (cancion == nullptr) {
        cout << "[x] Cancion no encontrada.\n";
        sistema->mostrarEstadisticas();
        return false;
    }
    cout << "\nCancion encontrada\n";
    cout << "  Titulo: " << cancion->getTitulo() << "\n";
    cout << "  ID: " << cancion->getId() << "\n";
    cout << "  Duracion: " << cancion->getDuracion() << " seg\n";

    Album* al = cancion->getAlbum();
    if (al) {
        cout << "  Album: " << al->getNombre() << "\n";
        Artista* art = al->getArtista();
        if (art) cout << "  Artista: " << art->getNombre() << "\n";
    }

    sistema->sumarIteraciones(2);
    if (lista->agregar(cancion->getId())) {
        cout << "[✓] Cancion agregada a favoritos.\n";
        sistema->sumarMemoria(sizeof(int));
        sistema->mostrarEstadisticas();
        return true;
    } else {
        cout << "[x] No se pudo agregar (ya existe o lista llena).\n";
        sistema->mostrarEstadisticas();
        return false;
    }
}
bool Usuario::quitarFavorito(UdeATunes* sistema) {
    if (lista->getCantidad() == 0) {
        cout << "[!] Tu lista de favoritos esta vacia.\n";
        sistema->mostrarEstadisticas();
        return false;
    }

    cout << "\n--- Quitar cancion de favoritos ---\n";
    cout << "Tienes " << lista->getCantidad() << " canciones en favoritos.\n";
    cout << "Ingrese el nombre de la cancion a eliminar: ";
    cin.ignore();
    string nombreCancion;
    getline(cin, nombreCancion);

    sistema->sumarIteraciones();
    Cancion* cancion = sistema->buscarCancionPorNombre(nombreCancion);

    if (cancion == nullptr) {
        cout << "[x] Cancion no encontrada en el sistema.\n";
        sistema->mostrarEstadisticas();
        return false;
    }
    if (lista->eliminar(cancion->getId())) {
        cout << "[✓] Cancion eliminada de favoritos.\n";
        sistema->restarMemoria(sizeof(int));
        sistema->mostrarEstadisticas();
        return true;
    } else {
        cout << "[x] Cancion no encontrada en tu lista.\n";
        sistema->mostrarEstadisticas();
        return false;
    }
}
void Usuario::ejecutarFavoritos(UdeATunes* sistema) {
    if (lista->getCantidad() == 0) {
        cout << "[!] Tu lista de favoritos esta vacia.\n";
        sistema->mostrarEstadisticas();
        return;
    }

    cout << "\n--- Reproducir favoritos ---\n";
    cout << "Canciones en tu lista: " << lista->getCantidad() << "\n";
    cout << "1) Reproducir en orden\n";
    cout << "2) Reproducir aleatoriamente\n";
    cout << "Elige: ";
    int opcion;
    cin >> opcion;

    if (!cin || (opcion != 1 && opcion != 2)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "[x] Opcion invalida.\n";
        sistema->mostrarEstadisticas();
        return;
    }

    bool aleatorio = (opcion == 2);
    sistema->sumarIteraciones();

    cout << "\nReproduciendo favoritos "
         << (aleatorio ? "aleatoriamente" : "en orden") << "...\n\n";

    int total = lista->getCantidad();
    int limite = (total > 5) ? 5 : total;

    // Si es aleatorio, mezclar primero
    if (aleatorio) {
        lista->mezclar();
    }

    for (int i = 0; i < limite; i++) {
        int idCancion = lista->getCancionEn(i);

        if (idCancion <= 0) continue;
        Cancion* c = sistema->buscarCancionPorId(idCancion);

        if (c == nullptr) {
            cout << "[!] Cancion con ID " << idCancion << " no encontrada.\n";
            continue;
        }
        Album* al = c->getAlbum();
        Artista* a = (al != nullptr) ? al->getArtista() : nullptr;

        sistema->mostrarInterfazReproduccion(c, a, al, true);
        sistema->sumarIteraciones(3);
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    cout << "\n[✓] Reproduccion de favoritos finalizada.\n";
    sistema->mostrarEstadisticas();
}
void Usuario::seguirLista(UdeATunes* sistema) {
    cout << "\n--- Seguir lista de otro usuario ---\n";
    cout << "Ingrese el nickname del usuario a seguir: ";
    string nicknameObjetivo;
    cin >> nicknameObjetivo;

    sistema->sumarIteraciones();

    if (nicknameObjetivo == nickname) {
        cout << "[!] No puedes seguir tu propia lista.\n";
        sistema->mostrarEstadisticas();
        return;
    }
    Usuario* otroUsuario = sistema->buscarUsuario(nicknameObjetivo);

    if (otroUsuario == nullptr) {
        cout << "[x] Usuario no encontrado.\n";
        sistema->mostrarEstadisticas();
        return;
    }

    if (otroUsuario->getMembresia() != "Premium") {
        cout << "[x] Solo puedes seguir listas de usuarios Premium.\n";
        sistema->mostrarEstadisticas();
        return;
    }

    ListaFavoritos* otraLista = otroUsuario->getLista();

    if (otraLista == nullptr || otraLista->getCantidad() == 0) {
        cout << "[!] El usuario '" << nicknameObjetivo
             << "' no tiene canciones en su lista.\n";
        sistema->mostrarEstadisticas();
        return;
    }

    sistema->sumarIteraciones();
    if (lista->seguirOtraLista(otraLista)) {
        int agregadas = lista->getCantidad();
        sistema->sumarMemoria(sizeof(int) * agregadas);
        sistema->mostrarEstadisticas();
    } else {
        sistema->mostrarEstadisticas();
    }
}
Usuario::~Usuario() {
    delete lista;
}
