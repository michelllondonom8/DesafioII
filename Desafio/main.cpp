#include <iostream>
#include <string>
#include "udeatunes.h" // donde se maneja toda la lógica del programa

using namespace std;

int main() {
    Sistema sistema; // clase central que controla todo

    // 1. Cargar los datos desde los archivos txt
    sistema.cargarDatos();

    // 2. Mostrar menú principal
    int opcion = 0;
    do {
        cout << "\n===== UdeATunes =====" << endl;
        cout << "1. Ingresar a la plataforma" << endl;
        cout << "2. Reproducción aleatoria" << endl;
        cout << "3. Mi lista de favoritos (solo Premium)" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
        case 1:
            sistema.ingresarPlataforma();
            break;
        case 2:
            sistema.reproducirAleatorio();
            break;
        case 3:
            sistema.menuFavoritos();
            break;
        case 4:
            cout << "Gracias por usar UdeATunes." << endl;
            break;
        default:
            cout << "Opción inválida. Intente de nuevo." << endl;
        }

    } while (opcion != 4);

    // 3. Guardar los datos actualizados en los archivos txt
    sistema.guardarDatos();

    return 0;
}
