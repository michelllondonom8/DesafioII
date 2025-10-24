// UdeATunes.cpp
#include "UdeATunes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

#define CAP_INI 4

UdeATunes::UdeATunes() {
    capacidadUsuarios = CAP_INI; capacidadArtistas = CAP_INI; capacidadCanciones = CAP_INI; capacidadPublicidades = CAP_INI;
    usuarios = new Usuario*[capacidadUsuarios];
    artistas = new Artista*[capacidadArtistas];
    canciones = new Cancion*[capacidadCanciones];
    publicidades = new MensajePublicidad[capacidadPublicidades];

    totalUsuarios = totalArtistas = totalCanciones = totalPublicidades = 0;
    for (int i = 0; i < capacidadUsuarios; ++i) usuarios[i] = nullptr;
    for (int i = 0; i < capacidadArtistas; ++i) artistas[i] = nullptr;
    for (int i = 0; i < capacidadCanciones; ++i) canciones[i] = nullptr;

    iteraciones = 0; memoriaEstimadaBytes = 0; ultimoAnuncioId = -1;
}

UdeATunes::~UdeATunes() {
    for (int i = 0; i < totalUsuarios; ++i) delete usuarios[i];
    for (int i = 0; i < totalArtistas; ++i) delete artistas[i];
    for (int i = 0; i < totalCanciones; ++i) delete canciones[i];
    delete[] usuarios;
    delete[] artistas;
    delete[] canciones;
    delete[] publicidades;
}

void UdeATunes::inicializar() {
    // inicializar generador aleatorio (solo una vez)
    MensajePublicidad::inicializarAzar();
    // contabilizar memoria base aproximada
    sumarMemoria(sizeof(UdeATunes));
    sumarMemoria(sizeof(Usuario*) * capacidadUsuarios);
    sumarMemoria(sizeof(Artista*) * capacidadArtistas);
    sumarMemoria(sizeof(Cancion*) * capacidadCanciones);
    sumarMemoria(sizeof(MensajePublicidad) * capacidadPublicidades);
    // nota: capacity_publicidades no existe como macro; en la compilación se añadirá memoria correctamente al aumentar capacidades
}

void UdeATunes::asegurarCapacidadUsuarios() {
    if (totalUsuarios < capacidadUsuarios) return;
    int nueva = capacidadUsuarios * 2;
    Usuario** tmp = new Usuario*[nueva];
    for (int i = 0; i < totalUsuarios; ++i) tmp[i] = usuarios[i];
    for (int i = totalUsuarios; i < nueva; ++i) tmp[i] = nullptr;
    delete[] usuarios;
    usuarios = tmp;
    sumarMemoria(sizeof(Usuario*) * (nueva - capacidadUsuarios));
    capacidadUsuarios = nueva;
}

void UdeATunes::asegurarCapacidadArtistas() {
    if (totalArtistas < capacidadArtistas) return;
    int nueva = capacidadArtistas * 2;
    Artista** tmp = new Artista*[nueva];
    for (int i = 0; i < totalArtistas; ++i) tmp[i] = artistas[i];
    for (int i = totalArtistas; i < nueva; ++i) tmp[i] = nullptr;
    delete[] artistas;
    artistas = tmp;
    sumarMemoria(sizeof(Artista*) * (nueva - capacidadArtistas));
    capacidadArtistas = nueva;
}

void UdeATunes::asegurarCapacidadCanciones() {
    if (totalCanciones < capacidadCanciones) return;
    int nueva = capacidadCanciones * 2;
    Cancion** tmp = new Cancion*[nueva];
    for (int i = 0; i < totalCanciones; ++i) tmp[i] = canciones[i];
    for (int i = totalCanciones; i < nueva; ++i) tmp[i] = nullptr;
    delete[] canciones;
    canciones = tmp;
    sumarMemoria(sizeof(Cancion*) * (nueva - capacidadCanciones));
    capacidadCanciones = nueva;
}

void UdeATunes::asegurarCapacidadPublicidades() {
    if (totalPublicidades < capacidadPublicidades) return;
    int nueva = capacidadPublicidades * 2;
    MensajePublicidad* tmp = new MensajePublicidad[nueva];
    for (int i = 0; i < totalPublicidades; ++i) tmp[i] = publicidades[i];
    delete[] publicidades;
    publicidades = tmp;
    sumarMemoria(sizeof(MensajePublicidad) * (nueva - capacidadPublicidades));
    capacidadPublicidades = nueva;
}

// -------------------------------------------------
// Carga de archivos: formatos simples (se explican abajo)
// -------------------------------------------------

void UdeATunes::cargarUsuariosDesdeArchivo(const char* ruta) {
    ifstream f(ruta);
    if (!f.is_open()) {
        cout << "No se pudo abrir " << ruta << endl;
        return;
    }
    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;
        if (line[0] == '#') continue;
        // formato: nickname|tipo|ciudad|pais|fecha
        stringstream ss(line);
        string nick, tipo, ciudad, pais, fecha;
        getline(ss, nick, '|');
        getline(ss, tipo, '|');
        getline(ss, ciudad, '|');
        getline(ss, pais, '|');
        getline(ss, fecha, '|');
        asegurarCapacidadUsuarios();
        usuarios[totalUsuarios++] = new Usuario(nick, tipo, ciudad, pais, fecha);
        sumarIteraciones();
        sumarMemoria(sizeof(Usuario));
    }
    f.close();
}

void UdeATunes::cargarPublicidadesDesdeArchivo(const char* ruta) {
    ifstream f(ruta);
    if (!f.is_open()) {
        cout << "No se pudo abrir " << ruta << endl;
        return;
    }
    string line;
    int idCounter = 1;
    while (getline(f, line)) {
        if (line.empty()) continue;
        if (line[0] == '#') continue;
        // formato: categoria|mensaje
        stringstream ss(line);
        string catStr;
        getline(ss, catStr, '|');
        string mensaje;
        getline(ss, mensaje);
        char cat = 'C';
        if (!catStr.empty()) cat = catStr[0];
        asegurarCapacidadPublicidades();
        publicidades[totalPublicidades] = MensajePublicidad(idCounter++, mensaje, cat);
        totalPublicidades++;
        sumarIteraciones();
        sumarMemoria(sizeof(MensajePublicidad));
    }
    f.close();
}

void UdeATunes::cargarCancionesDesdeArchivo(const char* ruta) {
    ifstream f(ruta);
    if (!f.is_open()) {
        cout << "No se pudo abrir " << ruta << endl;
        return;
    }
    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;
        if (line[0] == '#') continue;
        // formato: id|titulo|albumId|duracion|ruta_base (sin sufijo _128/_320)
        stringstream ss(line);
        int id; string idStr;
        string titulo; string albumId; int dur;
        string rutaBase;
        getline(ss, idStr, '|'); id = atoi(idStr.c_str());
        getline(ss, titulo, '|');
        getline(ss, albumId, '|');
        string durStr; getline(ss, durStr, '|'); dur = atoi(durStr.c_str());
        getline(ss, rutaBase, '|');
        asegurarCapacidadCanciones();
        // rutas completas: rutaBase + "_128.ogg" / "_320.ogg"
        string ruta128 = rutaBase + "_128.ogg";
        string ruta320 = rutaBase + "_320.ogg";
        canciones[totalCanciones++] = new Cancion(id, titulo, dur, ruta128, ruta320, albumId);
        sumarIteraciones();
        sumarMemoria(sizeof(Cancion));
    }
    f.close();
}

void UdeATunes::cargarArtistasDesdeArchivo(const char* ruta) {
    ifstream f(ruta);
    if (!f.is_open()) {
        cout << "No se pudo abrir " << ruta << endl;
        return;
    }
    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;
        if (line[0] == '#') continue;
        // formato simple: id|nombre|edad|pais|seguidores|tendencia
        stringstream ss(line);
        string idStr, nombre, edadStr, pais, seguidoresStr, tendenciaStr;
        getline(ss, idStr, '|');
        getline(ss, nombre, '|');
        getline(ss, edadStr, '|');
        getline(ss, pais, '|');
        getline(ss, seguidoresStr, '|');
        getline(ss, tendenciaStr, '|');
        asegurarCapacidadArtistas();
        artistas[totalArtistas++] = new Artista(nombre, pais);
        sumarIteraciones();
        sumarMemoria(sizeof(Artista));
    }
    f.close();
}
void UdeATunes::reproducirAleatorio(int k) {
    cout << "[♪] Reproduciendo aleatoriamente " << k << " canciones...\n";
    for (int i = 0; i < k && i < totalCanciones; i++) {
        Cancion* c = canciones[i];
        cout << "----------------------------------------------------\n";
        cout << "Titulo: " << c->getTitulo() << "\n";
        cout << "Duraciom: " << c->getDuracion() << " segundos\n";
        cout << "Ruta del archivo: " << c->getRutaBaja() << "\n";
        cout << "----------------------------------------------------\n";
        sumarIteraciones();
        sumarMemoria(sizeof(Cancion));
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// -------------------------------------------------
// interfaz de reproducción (impresión similar a la imagen)
// -------------------------------------------------
void UdeATunes::mostrarInterfazReproduccion(Cancion* c, Artista* artista, Album* album, bool esPremium) {
    cout << "----------------------------------------------------\n";
    // publicidad si aplica
    if (!esPremium && totalPublicidades > 0) {
        int idx = MensajePublicidad::elegirAleatorio(publicidades, totalPublicidades, ultimoAnuncioId);
        if (idx >= 0) {
            cout << "Mensaje publicitario (Si aplica): ";
            publicidades[idx].mostrar();
            ultimoAnuncioId = publicidades[idx].getId();
        }
        cout << "----------------------------------------------------\n";
    }
    if (artista) cout << "Cantante: " << artista->getNombre() << "\n";
    if (album) cout << "Album: " << album->getNombre() << "\n";
    if (album) cout << "Ruta a la portada del album:\n" << " " << album->getNombre() << " (ver archivo)\n";
    cout << "----------------------------------------------------\n";
    cout << "Titulo de la cancion reproducida: " << c->getTitulo() << "\n";
    cout << "Ruta al archivo de audio: " << (esPremium ? c->getRutaAlta() : c->getRutaBaja()) << "\n";
    cout << "Duracion: " << c->getDuracion() << " segundos\n";
    cout << "----------------------------------------------------\n";
    cout << "Opciones de reproduccion:\n1.- Reproducir  2.- Detener  3.- Siguiente  4.- Repetir\n";
    cout << "*Todas las opciones que apliquen\n";
    cout << "----------------------------------------------------\n";
}

// -------------------------------------------------
// Menú principal (simplificado pero cumple requerimientos)
// -------------------------------------------------
void UdeATunes::menuPrincipal() {
    int op = -1;
    while (op != 0) {
        cout << "\n=== UdeATunes ===\n";
        cout << "1) Cargar archivos (usuarios, canciones, publicidades, artistas)\n";
        cout << "2) Iniciar sesion (por nickname)\n";
        cout << "3) Reproduccion aleatoria (K=5)\n";
        cout << "4) Ejecutar lista de favoritos (si eres Premium)\n";
        cout << "5) Mostrar resumen/estadisticas\n";
        cout << "0) Salir\n";
        cout << "Elige: ";
        if (!(cin >> op)) { cin.clear(); cin.ignore(1000,'\n'); op = -1; continue; }
        switch (op) {
        case 1: {
            char ruta[256];
            cout << "Archivo usuarios (ej: usuarios.txt): "; cin >> ruta; cargarUsuariosDesdeArchivo(ruta);
            cout << "Archivo canciones (ej: canciones.txt): "; cin >> ruta; cargarCancionesDesdeArchivo(ruta);
            cout << "Archivo publicidades (ej: publicidad.txt): "; cin >> ruta; cargarPublicidadesDesdeArchivo(ruta);
            cout << "Archivo artistas (ej: artistas.txt): "; cin >> ruta; cargarArtistasDesdeArchivo(ruta);
            break;
        }
        case 2: {
            string nick;
            cout << "Nickname: "; cin >> nick;
            int idx = -1;
            for (int i = 0; i < totalUsuarios; ++i) {
                if (usuarios[i]->getNickname() == nick) { idx = i; break; }
            }
            if (idx == -1) cout << "Usuario no encontrado\n";
            else {
                cout << "Bienvenido " << usuarios[idx]->getNickname() << " (" << usuarios[idx]->getMembresia() << ")\n";
                // menú de usuario (simplificado)
                bool salirUser = false;
                while (!salirUser) {
                    cout << "1) Ejecutar lista de favoritos\n2) Seguir lista de otro usuario\n0) Volver\nElige: ";
                    int o; cin >> o;
                    if (o == 0) break;
                    if (o == 1) {
                        ListaFavoritos* L = usuarios[idx]->getListaFavoritos();
                        if (L) L->ejecutarLista();
                        else cout << "No tienes lista de favoritos (solo Premium)\n";
                    } else if (o == 2) {
                        string otro;
                        cout << "Nickname a seguir: "; cin >> otro;
                        int idxOtro = -1;
                        for (int j = 0; j < totalUsuarios; ++j) if (usuarios[j]->getNickname() == otro) { idxOtro = j; break; }
                        if (idxOtro == -1) cout << "Usuario a seguir no encontrado\n";
                        else {
                            ListaFavoritos* Lmio = usuarios[idx]->getListaFavoritos();
                            ListaFavoritos* Lotro = usuarios[idxOtro]->getListaFavoritos();
                            if (!Lmio) cout << "No tienes lista (solo Premium)\n";
                            else if (!Lotro) cout << "El usuario a seguir no tiene lista de favoritos\n";
                            else {
                                Lmio->seguirOtraLista(Lotro);
                            }
                        }
                    }
                }
            }
            break;
        }
        case 3: {
            reproducirAleatorio(5);
            break;
        }
        case 4: {
            cout << "Ingresa tu nickname: ";
            string nick; cin >> nick;
            int idx = -1;
            for (int i = 0; i < totalUsuarios; ++i) if (usuarios[i]->getNickname() == nick) { idx = i; break; }
            if (idx == -1) { cout << "Usuario no encontrado\n"; break; }
            ListaFavoritos* L = usuarios[idx]->getListaFavoritos();
            if (!L) { cout << "Eres estandar; no tienes lista de favoritos\n"; break; }
            cout << "¿Reproducir aleatorio? 1=si 0=no: ";
            int a; cin >> a;
            L->ejecutarLista(a==1);
            break;
        }
        case 5: {
            cout << "\n--- Resumen ---\n";
            cout << "Usuarios: " << totalUsuarios << " | Artistas: " << totalArtistas << " | Canciones: " << totalCanciones << " | Publicidades: " << totalPublicidades << "\n";
            cout << "Iteraciones: " << iteraciones << " | Memoria estimada (bytes): " << memoriaEstimadaBytes << "\n";
            break;
        }
        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion no valida\n";
        }
    }
}
