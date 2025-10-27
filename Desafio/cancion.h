#define CANCION_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

class Album;

class Cancion {
private:
    int id;
    std::string titulo;
    int duracion;
    std::string rutaBaja;
    std::string rutaAlta;
    std::string albumID;
    long reproducciones;
    Album* album;

public:
    Cancion();
    Cancion(int _id, const std::string& _titulo, int _duracion,
            const std::string& _rutaBaja, const std::string& _rutaAlta, const std::string& _albumID);
    Cancion(const Cancion& otra);
    Cancion& operator=(const Cancion& otra);
    ~Cancion();

    void sumarReproduccion();

    int getId() const;
    std::string getTitulo() const;
    int getDuracion() const;
    long getReproducciones() const;
    std::string getRutaAlta() const;
    std::string getRutaBaja() const;
    std::string getAlbumID() const;
    void setAlbum(Album* a);
    Album* getAlbum() const;

    // === Sobrecargas agregadas según el PDF del desafío ===
    bool operator==(const Cancion& otra) const;                    // Compara dos canciones por su ID
    friend std::ostream& operator<<(std::ostream& os, const Cancion& c);  // Muestra la canción en consola
};

#endif
