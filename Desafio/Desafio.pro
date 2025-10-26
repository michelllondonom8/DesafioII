TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        album.cpp \
        artista.cpp \
        cancion.cpp \
        colaborador.cpp \
        listafavoritos.cpp \
        main.cpp \
        mensajepublicidad.cpp \
        udeatunes.cpp \
        usuario.cpp

HEADERS += \
    album.h \
    artista.h \
    cancion.h \
    colaborador.h \
    listafavoritos.h \
    mensajepublicidad.h \
    udeatunes.h \
    usuario.h

DISTFILES += \
    build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/albumes.txt \
    build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/artistas.txt \
    build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/canciones.txt \
    build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/favoritos.txt \
    build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/publicidad.txt \
    build/Desktop_Qt_6_7_3_MinGW_64_bit-Debug/usuarios.txt
