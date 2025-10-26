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
    capacidadUsuarios = CAP_INI; capacidadArtistas = CAP_INI; capacidadCanciones = CAP_INI; capacidadAlbumes = CAP_INI; capacidadPublicidades = CAP_INI;
    usuarios = new Usuario*[capacidadUsuarios];
    artistas = new Artista*[capacidadArtistas];
    canciones = new Cancion*[capacidadCanciones];
    albumes = new Album*[capacidadAlbumes];
    publicidades = new MensajePublicidad[capacidadPublicidades];

    totalUsuarios = totalArtistas = totalCanciones = totalPublicidades = 0;
    for (int i = 0; i < capacidadUsuarios; ++i) usuarios[i] = nullptr;
    for (int i = 0; i < capacidadArtistas; ++i) artistas[i] = nullptr;
    for (int i = 0; i < capacidadAlbumes; ++i) albumes[i] = nullptr;
    for (int i = 0; i < capacidadCanciones; ++i) canciones[i] = nullptr;

    iteraciones = 0; memoriaEstimadaBytes = 0; ultimoAnuncioId = -1;
}

UdeATunes::~UdeATunes() {
    for (int i = 0; i < totalUsuarios; ++i) delete usuarios[i];
    for (int i = 0; i < totalArtistas; ++i) delete artistas[i];
    for (int i = 0; i < totalCanciones; ++i) delete canciones[i];
    for (int i = 0; i < totalAlbumes; ++i) delete albumes[i];
    delete[] usuarios;
    delete[] artistas;
    delete[] canciones;
    delete[] publicidades;
    delete[] albumes;
}
Cancion* UdeATunes::buscarCancionPorId(int id) {
    for (int i = 0; i < totalCanciones; i++) {
        sumarIteraciones();
        if (canciones[i]->getId() == id) {
            return canciones[i];
        }
    }
    return nullptr;
}

Cancion* UdeATunes::buscarCancionPorNombre(const string& nombre) {
    for (int i = 0; i < totalCanciones; i++) {
        sumarIteraciones();

        string tituloCancion = canciones[i]->getTitulo();
        string nombreLower = nombre;
        string tituloLower = tituloCancion;

        for (char& c : nombreLower) c = tolower(c);
        for (char& c : tituloLower) c = tolower(c);

        if (tituloLower == nombreLower) {
            return canciones[i];
        }
    }
    return nullptr;
}

Usuario* UdeATunes::buscarUsuario(const string& nickname) {
    for (int i = 0; i < totalUsuarios; i++) {
        sumarIteraciones();
        if (usuarios[i]->getNickname() == nickname) {
            return usuarios[i];
        }
    }
    return nullptr;
}
void UdeATunes::inicializar() {
    MensajePublicidad::inicializarAzar();
    sumarMemoria(sizeof(UdeATunes));
    sumarMemoria(sizeof(Usuario*) * capacidadUsuarios);
    sumarMemoria(sizeof(Artista*) * capacidadArtistas);
    sumarMemoria(sizeof(Cancion*) * capacidadCanciones);
    sumarMemoria(sizeof(MensajePublicidad) * capacidadPublicidades);
}

void UdeATunes::cargarArchivos() {
    cout << "\nCargando archivos predeterminados...\n";

    const char* usuariosFile   = "usuarios.txt";
    const char* cancionesFile  = "canciones.txt";
    const char* publicidadFile = "publicidad.txt";
    const char* artistasFile   = "artistas.txt";
    const char* albumesFile    = "albumes.txt";

    cargarArtistasDesdeArchivo(artistasFile);
    cargarAlbumesDesdeArchivo(albumesFile);
    cargarCancionesDesdeArchivo(cancionesFile);
    cargarUsuariosDesdeArchivo(usuariosFile);
    cargarPublicidadesDesdeArchivo(publicidadFile);
    enlazarCancionesConAlbumesYArtistas();


    cout << "Carga completa.\n";
    cout << "Usuarios: " << totalUsuarios
         << ", Canciones: " << totalCanciones
         << ", Publicidades: " << totalPublicidades
         << ", Artistas: " << totalArtistas << endl;
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
void UdeATunes::asegurarCapacidadAlbumes() {
    if (totalAlbumes < capacidadAlbumes) return;
    int nueva = capacidadAlbumes * 2;
    Album** tmp = new Album*[nueva];
    for (int i = 0; i < totalAlbumes; ++i) tmp[i] = albumes[i];
    for (int i = totalAlbumes; i < nueva; ++i) tmp[i] = nullptr;
    delete[] albumes;
    albumes = tmp;
    sumarMemoria(sizeof(Album*) * (nueva - capacidadAlbumes));
    capacidadAlbumes = nueva;
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
void UdeATunes::cargarCancionesDesdeArchivo(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error al abrir " << ruta << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty() || linea[0] == '#') continue;
        string idStr, titulo, albumNombre, duracionStr, rutaBase;
        stringstream ss(linea);
        getline(ss, idStr, '|');
        getline(ss, titulo, '|');
        getline(ss, albumNombre, '|');
        getline(ss, duracionStr, '|');
        getline(ss, rutaBase, '|');

        int id = stoi(idStr);
        int duracion = stoi(duracionStr);

        asegurarCapacidadCanciones();

        Cancion* c = new Cancion(id, titulo, duracion, rutaBase, rutaBase, albumNombre);
        canciones[totalCanciones++] = c;

        sumarIteraciones();
        sumarMemoria(sizeof(Cancion));
    }

    archivo.close();
    cout << "Canciones cargadas: " << totalCanciones << endl;
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
void UdeATunes::cargarAlbumesDesdeArchivo(const string& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cout << "Error al abrir " << ruta << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty() || linea[0] == '#') continue;
        string id, idArtista, nombre, genero, fecha, duracionStr, sello, puntuacionStr, rutaPortada;
        stringstream ss(linea);

        getline(ss, id, '|');
        getline(ss, idArtista, '|');
        getline(ss, nombre, '|');
        getline(ss, genero, '|');
        getline(ss, fecha, '|');
        getline(ss, duracionStr, '|');
        getline(ss, sello, '|');
        getline(ss, puntuacionStr, '|');
        getline(ss, rutaPortada, '|');

        int duracion = stoi(duracionStr);
        int puntuacion = stoi(puntuacionStr);
        Album* nuevo = new Album(id, idArtista, nombre, genero, fecha, duracion, sello, puntuacion, rutaPortada);
        Artista* artistaAsociado = nullptr;
        for (int i = 0; i < totalArtistas; i++) {
            if (to_string(i + 10001) == idArtista) {
                artistaAsociado = artistas[i];
                break;
            }
        }

        if (artistaAsociado != nullptr) {
            artistaAsociado->agregarAlbum(nuevo);
            nuevo->setArtista(artistaAsociado);
        }

        albumes[totalAlbumes++] = nuevo;
        asegurarCapacidadAlbumes();
    }

    archivo.close();
}
void UdeATunes::reproducirAleatorio(int k, bool esPremium) {
    if (totalCanciones == 0) {
        cout << "No hay canciones disponibles.\n";
        return;
    }

    cout << "\nReproduciendo aleatoriamente hasta " << k << " canciones...\n\n";

    if (!esPremium) {
        int contadorPublicidad = 0;
        for (int i = 0; i < k; i++) {
            int indiceAleatorio = rand() % totalCanciones;
            Cancion* cancionActual = canciones[indiceAleatorio];

            Album* al = cancionActual->getAlbum();
            Artista* a = (al != nullptr) ? al->getArtista() : nullptr;

            cout << "\n====================================================\n";
            if (totalPublicidades > 0 && contadorPublicidad % 2 == 0) {
                int idx = MensajePublicidad::elegirAleatorio(publicidades, totalPublicidades, ultimoAnuncioId);
                if (idx >= 0) {
                    cout << ">>> MENSAJE PUBLICITARIO <<<\n";
                    cout << publicidades[idx].getMensaje() << "\n";
                    cout << "Categoria: " << publicidades[idx].getCategoria() << "\n";
                    ultimoAnuncioId = publicidades[idx].getId();
                    cout << "====================================================\n";
                }
            }

            cout << "REPRODUCIENDO AUTOMATICAMENTE\n";
            cout << "====================================================\n";
            cout << "Cantante: " << (a ? a->getNombre() : "(Artista desconocido)") << "\n";
            cout << "Album: " << (al ? al->getNombre() : "(Album no disponible)") << "\n";
            if (al) cout << "Portada: " << al->getRutaPortada() << "\n";
            cout << "----------------------------------------------------\n";
            cout << "Titulo: " << cancionActual->getTitulo() << "\n";
            cout << "Duracion: " << cancionActual->getDuracion() << " segundos\n";
            cout << "Ruta: " << cancionActual->getRutaBaja() << "\n";
            cout << "====================================================\n";
            cout << "Progreso: [" << (i + 1) << "/" << k << "]\n";
            cout << "====================================================\n\n";

            cout << "[Reproduciendo... espere 3 segundos]\n\n";
            this_thread::sleep_for(chrono::seconds(3));

            contadorPublicidad++;
            sumarIteraciones();
        }

        cout << "\n====================================================\n";
        cout << "[Reproduccion de " << k << " canciones finalizada]\n";
        cout << "====================================================\n\n";

        bool continuarMenu = true;
        while (continuarMenu) {
            cout << "--- OPCIONES DE REPRODUCCION ESTANDAR ---\n";
            cout << "1. Detener (salir de reproduccion)\n";
            cout << "2. Iniciar (reproducir otras " << k << " canciones)\n";
            cout << "Seleccione una opcion: ";

            int opcion;
            cin >> opcion;

            switch(opcion) {
            case 1:
                cout << "\nSaliendo de reproduccion...\n";
                continuarMenu = false;
                break;

            case 2:
                cout << "\nIniciando nueva reproduccion...\n\n";
                reproducirAleatorio(k, false);
                continuarMenu = false;
                break;

            default:
                cout << "\nOpcion invalida. Intente de nuevo.\n\n";
            }
        }

    } else {
        const int MAX_HISTORIAL = 4;
        Cancion* historial[MAX_HISTORIAL] = {nullptr};
        int totalEnHistorial = 0;

        bool reproduciendo = true;
        bool modoRepetir = false;
        int cancionesReproducidas = 0;
        Cancion* cancionActual = nullptr;
        bool pausado = false;

        while (reproduciendo && cancionesReproducidas < k) {
            if (!modoRepetir) {
                int indiceAleatorio = rand() % totalCanciones;
                cancionActual = canciones[indiceAleatorio];

                historial[totalEnHistorial % MAX_HISTORIAL] = cancionActual;
                totalEnHistorial++;
            }

            Album* al = cancionActual->getAlbum();
            Artista* a = (al != nullptr) ? al->getArtista() : nullptr;

            cout << "\n====================================================\n";
            cout << "REPRODUCIENDO ";
            if (pausado) {
                cout << "(PAUSADO)\n";
            } else {
                cout << "\n";
            }
            cout << "====================================================\n";
            cout << "Cantante: " << (a ? a->getNombre() : "(Artista desconocido)") << "\n";
            cout << "Album: " << (al ? al->getNombre() : "(Album no disponible)") << "\n";
            if (al) cout << "Portada: " << al->getRutaPortada() << "\n";
            cout << "----------------------------------------------------\n";
            cout << "Titulo: " << cancionActual->getTitulo() << "\n";
            cout << "Duracion: " << cancionActual->getDuracion() << " segundos\n";
            cout << "Ruta: " << cancionActual->getRutaAlta() << "\n";
            cout << "====================================================\n";
            cout << "Estado: REPETIR [" << (modoRepetir ? "ON" : "OFF") << "]\n";
            cout << "Progreso: [" << (cancionesReproducidas + 1) << "/" << k << "]\n";
            cout << "====================================================\n\n";

            cout << "--- OPCIONES DE REPRODUCCION PREMIUM ---\n";

            if (pausado) {
                cout << "1. Iniciar reproduccion\n";
            } else {
                cout << "1. Detener reproduccion\n";
            }

            cout << "2. Siguiente cancion\n";

            int cancionesDisponiblesAtras = (totalEnHistorial > MAX_HISTORIAL) ? MAX_HISTORIAL : (totalEnHistorial - 1);
            if (cancionesDisponiblesAtras > 0) {
                cout << "3. Cancion previa (hasta " << cancionesDisponiblesAtras << " hacia atras)\n";
            }

            cout << "4. " << (modoRepetir ? "Desactivar" : "Activar") << " modo repetir\n";
            cout << "5. Continuar (avanza automaticamente en 3s)\n";
            cout << "0. Salir de reproduccion\n";
            cout << "\nSeleccione una opcion: ";

            int opcion;
            cin >> opcion;

            switch(opcion) {
            case 1:
                pausado = !pausado;
                cout << (pausado ? "\nReproduccion pausada.\n" : "\nReproduccion iniciada.\n");
                break;

            case 2:
                if (!pausado) {
                    cout << "\nSiguiente cancion...\n";
                    modoRepetir = false;
                    if (!modoRepetir) cancionesReproducidas++;
                    this_thread::sleep_for(chrono::seconds(1));
                } else {
                    cout << "\nDebe iniciar la reproduccion primero.\n";
                }
                break;

            case 3: {
                int cancionesAtras = (totalEnHistorial > MAX_HISTORIAL) ? MAX_HISTORIAL : (totalEnHistorial - 1);

                if (cancionesAtras > 0 && !pausado) {
                    int posActual = (totalEnHistorial - 1) % MAX_HISTORIAL;
                    int posPrev = (posActual - 1 + MAX_HISTORIAL) % MAX_HISTORIAL;

                    cancionActual = historial[posPrev];
                    totalEnHistorial--;

                    cout << "\nCancion previa...\n";
                    modoRepetir = false;
                    this_thread::sleep_for(chrono::seconds(1));
                } else if (pausado) {
                    cout << "\nDebe iniciar la reproduccion primero.\n";
                } else {
                    cout << "\nNo hay canciones previas.\n";
                }
                break;
            }

            case 4:
                modoRepetir = !modoRepetir;
                cout << "\nModo repetir: " << (modoRepetir ? "ACTIVADO" : "DESACTIVADO") << "\n";
                break;

            case 5:
                if (!pausado) {
                    cout << "\nContinuando reproduccion automaticamente...\n";
                    this_thread::sleep_for(chrono::seconds(3));
                    if (!modoRepetir) cancionesReproducidas++;
                } else {
                    cout << "\nDebe iniciar la reproduccion primero.\n";
                }
                break;

            case 0:
                cout << "\nReproduccion finalizada por el usuario.\n";
                reproduciendo = false;
                break;

            default:
                cout << "\nOpcion invalida.\n";
            }

            sumarIteraciones();
        }

        cout << "\n[Reproduccion finalizada]\n";
        cout << "Total de canciones reproducidas: " << cancionesReproducidas << "\n";
    }
}
void UdeATunes::menuEstandar(Usuario*) {
    bool salir = false;
    while (!salir) {
        cout << "\n--- Menu Estandar ---\n";
        cout << "1) Reproduccion aleatoria\n";
        cout << "2) Ver estadisticas\n";
        cout << "0) Cerrar sesion\n";
        cout << "Elige: ";
        int op; cin >> op;

        switch (op) {
        case 1:
            reproducirAleatorio(5, false);
            break;
        case 2:
            mostrarEstadisticas();
            break;
        case 0:
            salir = true;
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    }
}
void UdeATunes::enlazarCancionesConAlbumesYArtistas() {
    cout << "\n[Enlazando relaciones...]\n";

    int cancionesEnlazadas = 0;
    int albumesEnlazados = 0;
    for (int i = 0; i < totalAlbumes; ++i) {
        Album* album = albumes[i];
        string idArtista = album->getIdArtista();
        int idArtistaInt = stoi(idArtista);

        for (int j = 0; j < totalArtistas; ++j) {
            if ((10001 + j) == idArtistaInt) {
                album->setArtista(artistas[j]);
                artistas[j]->agregarAlbum(album);
                albumesEnlazados++;
                break;
            }
        }
        sumarIteraciones();
    }
    for (int c = 0; c < totalCanciones; ++c) {
        Cancion* cancion = canciones[c];
        string nombreAlbumCancion = cancion->getAlbumID();
        Album* albumEncontrado = nullptr;

        for (int a = 0; a < totalAlbumes; ++a) {
            if (albumes[a]->getNombre() == nombreAlbumCancion) {
                albumEncontrado = albumes[a];
                break;
            }
        }

        if (albumEncontrado != nullptr) {
            cancion->setAlbum(albumEncontrado);
            albumEncontrado->agregarCancion(cancion);
            cancionesEnlazadas++;
        }

        sumarIteraciones();
    }
    if (cancionesEnlazadas < totalCanciones) {
        cout << "ADVERTENCIA: " << (totalCanciones - cancionesEnlazadas)
        << " canciones no pudieron enlazarse con un album.\n";
    }
    cout << "Albumes enlazados: " << albumesEnlazados << "/" << totalAlbumes << "\n";
    cout << "Canciones enlazadas: " << cancionesEnlazadas << "/" << totalCanciones << "\n";
}
void UdeATunes::menuPremium(Usuario* user) {
    bool salir = false;
    while (!salir) {
        cout << "\n--- Menu Premium ---\n";
        cout << "1) Agregar cancion a favoritos\n";
        cout << "2) Quitar cancion de favoritos\n";
        cout << "3) Ejecutar lista de favoritos\n";
        cout << "4) Seguir lista de otro usuario\n";
        cout << "5) Dejar de seguir lista\n";
        cout << "6) Ver estadisticas\n";
        cout << "0) Cerrar sesion\n";
        cout << "Elige: ";
        int op; cin >> op;

        switch (op) {
        case 1:
            user->agregarFavorito(this);
            break;

        case 2:
            user->quitarFavorito(this);
            break;

        case 3:
            user->ejecutarFavoritos(this);
            break;

        case 4:
            user->seguirLista(this);
            break;

        case 5:
            user->dejarDeSeguir(this);
            break;
        case 6:
            mostrarEstadisticas();
            break;

        case 0:
            salir = true;
            break;

        default:
            cout << "Opcion invalida.\n";
        }
    }
}
void UdeATunes::menuPrincipal() {
    cargarArchivos();

    cout << "\n=== Bienvenido a UdeATunes ===\n";
    bool salir = false;

    while (!salir) {
        cout << "\n1) Iniciar sesion\n";
        cout << "0) Salir del sistema\n";
        cout << "Elige una opcion: ";
        int op;
        cin >> op;
        if (!cin) { cin.clear(); cin.ignore(1000, '\n'); continue; }

        switch (op) {
        case 1: {
            string nick;
            cout << "\nIngrese su nickname: ";
            cin >> nick;

            Usuario* user = nullptr;
            for (int i = 0; i < totalUsuarios; ++i) {
                if (usuarios[i]->getNickname() == nick) {
                    user = usuarios[i];
                    break;
                }
            }

            if (!user) {
                cout << "Usuario no encontrado.\n";
                break;
            }

            cout << "\nBienvenido " << user->getNickname()
                 << " (" << user->getMembresia() << ")\n";

            if (user->getMembresia() == "Premium")
                menuPremium(user);
            else
                menuEstandar(user);

            break;
        }

        case 0:
            cout << "\nGracias por usar UdeATunes. ¡Hasta pronto!\n";
            salir = true;
            break;

        default:
            cout << "Opcion invalida.\n";
        }
    }
}
void UdeATunes::mostrarEstadisticas() const {
    cout << "\n--- Estadisticas del sistema ---\n";
    cout << "Usuarios: " << totalUsuarios
         << " | Canciones: " << totalCanciones
         << " | Artistas: " << totalArtistas
         << " | Publicidades: " << totalPublicidades << "\n";
    cout << "Iteraciones totales: " << iteraciones
         << " | Memoria estimada: " << memoriaEstimadaBytes << " bytes\n";
}
void UdeATunes::sumarIteraciones(unsigned long n) {
    iteraciones += n;
}

void UdeATunes::sumarMemoria(size_t bytes) {
    memoriaEstimadaBytes += bytes;
}
void UdeATunes::restarMemoria(size_t bytes) {
    if (memoriaEstimadaBytes >= bytes) {
        memoriaEstimadaBytes -= bytes;
    } else {
        memoriaEstimadaBytes = 0;
    }
}
