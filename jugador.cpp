#include <iostream>
#include "jugador.h"
#include "mazmorra.h"
using namespace std;

Jugador::Jugador(int startX, int startY) {
    x = startX;
    y = startY;
    vida = 100;
    dano = 20;
    rango = 1;
    habilidad = "";
    direccion = "arriba";
    recibiendoDano = false;
    llaves = 0;
    llavesJefe = 0;
    pasos = 0;
    cofresAbiertos = 0;
    puertasAbiertas = 0;
    enemigosDerrotados = 0;
    numBombas = 3;
    usandoHabilidad = false;
    atacando = false;
    enSalaJefe = false;
    haGanado = false;
}

void Jugador::mover(char direccionInput, Mazmorra* mazmorra) {
    string nuevaDireccion;

    switch (direccionInput) {
        case 'w': case 'W': nuevaDireccion = "arriba"; break;
        case 's': case 'S': nuevaDireccion = "abajo"; break;
        case 'a': case 'A': nuevaDireccion = "izquierda"; break;
        case 'd': case 'D': nuevaDireccion = "derecha"; break;
        default:
            cout << "Dirección no válida. Usa W/A/S/D." << endl;
            return;
    }

    if (direccion != nuevaDireccion) {
        direccion = nuevaDireccion;
        cout << "Link gira hacia " << direccion << endl;
        return;
    }

    int nuevaFila = y;
    int nuevaColumna = x;

    if (direccion == "arriba") nuevaFila--;
    else if (direccion == "abajo") nuevaFila++;
    else if (direccion == "izquierda") nuevaColumna--;
    else if (direccion == "derecha") nuevaColumna++;

    char celdaDestino = mazmorra->obtenerCelda(nuevaFila, nuevaColumna);

    if (celdaDestino == 'X' || celdaDestino == 'P' || celdaDestino == 'C' ||
        celdaDestino == 'K' || celdaDestino == 'Y' || celdaDestino == 'E' ||
        celdaDestino == 'J' || celdaDestino == 'U' || celdaDestino == 'A') {
        cout << "No puedes moverte ahí, hay un obstáculo: " << celdaDestino << endl;
        return;
    }

    x = nuevaColumna;
    y = nuevaFila;
    pasos++;
    cout << "Link se movió hacia " << direccion << ". Posición: (" << x << ", " << y << ")" << endl;
}

void Jugador::recibirDano(int cantidad) {
    if (cantidad <= 0) return;

    recibiendoDano = true;
    vida -= cantidad;

    if (vida < 0) vida = 0;

    cout << "Link recibió " << cantidad << " puntos de daño! Vida restante: " << vida << endl;

    if (vida == 0) {
        cout << "Link ha sido derrotado!" << endl;
    }

    recibiendoDano = false;
}

void Jugador::curar(int cantidad) {
    if (cantidad <= 0) return;

    vida += cantidad;
    if (vida > 100) vida = 100;

    cout << "Link se curó " << cantidad << " puntos de vida. Vida actual: " << vida << endl;
}

void Jugador::salto(Mazmorra* mazmorra, char direccion) {
    int dx = 0, dy = 0;
    if (direccion == 'w') dy = -2;
    else if (direccion == 'a') dx = -2;
    else if (direccion == 's') dy = 2;
    else if (direccion == 'd') dx = 2;

    int destinoX = x + dx;
    int destinoY = y + dy;
    char celdaDestino = mazmorra->obtenerCelda(destinoY, destinoX);
    if (celdaDestino == '-' || celdaDestino == ' ') {
        setPosicion(destinoX, destinoY);
    } else {
        cout << "¡Hay un obstáculo! Perdiste el turno." << endl;
    }
}

void Jugador::usarEscudo(Mazmorra*, char direccion) {
    int index = 0;

    if (direccion == 'w') index = 0;
    else if (direccion == 's') index = 1;
    else if (direccion == 'd') index = 2;
    else if (direccion == 'a') index = 3;

    if (enemigosQueAtacan[index]) {
        cout << "Escudo activado contra ataque en dirección " << direccion << endl;
    } else {
        cout << "No hay enemigos atacando en esa dirección." << endl;
    }
}

void Jugador::usarArco(Mazmorra* mazmorra, char) {
    for (auto& enemigo : mazmorra->obtenerEnemigos()) {
        int distX = abs(enemigo.getX() - x);
        int distY = abs(enemigo.getY() - y);
        if (distX <= 2 && distY <= 2) {
            enemigo.recibirDano(10);
            cout << "Disparo con el arco a enemigo en (" << enemigo.getX() << ", " << enemigo.getY() << ")" << endl;
        }
    }
}

void Jugador::usarBomba(Mazmorra* mazmorra) {
    if (numBombas <= 0) {
        cout << "No tienes bombas disponibles." << endl;
        return;
    }

    for (auto& enemigo : mazmorra->obtenerEnemigos()) {
        if (abs(enemigo.getX() - x) <= 1 && abs(enemigo.getY() - y) <= 1) {
            enemigo.recibirDano(100);
            cout << "¡Bomba explotó cerca de un enemigo!" << endl;
        }
    }

    int frenteY = y + 1;
    char celda = mazmorra->obtenerCelda(frenteY, x);
    if (celda == 'X') {
        mazmorra->modificarCelda(frenteY, x, '-');
        cout << "¡Bomba destruyó una pared!" << endl;
    }

    numBombas--;
}

void Jugador::usarGancho(Mazmorra* mazmorra, char direccion) {
    int dx = 0, dy = 0;
    if (direccion == 'w') dy = -1;
    else if (direccion == 'a') dx = -1;
    else if (direccion == 's') dy = 1;
    else if (direccion == 'd') dx = 1;

    int destinoX = x + dx;
    int destinoY = y + dy;
    char celda = mazmorra->obtenerCelda(destinoY, destinoX);
    if (celda == 'X' || celda == 'C' || celda == 'K') {
        setPosicion(destinoX, destinoY);
        for (auto& enemigo : mazmorra->obtenerEnemigos()) {
            if (enemigo.getX() == destinoX && enemigo.getY() == destinoY) {
                enemigo.recibirDano(5);
            }
        }
    } else {
        cout << "No puedes usar el gancho aquí." << endl;
    }
}

void Jugador::usarHabilidad(Mazmorra* mazmorra) {
    cout << "Selecciona una habilidad:\n1. Salto\n2. Escudo\n3. Arco\n4. Bomba\n5. Gancho\n";
    int opcion;
    cin >> opcion;
    char direccion;

    if (opcion >= 1 && opcion <= 3 || opcion == 5) {
        cout << "Indica la dirección (w/a/s/d): ";
        cin >> direccion;
    }

    switch (opcion) {
        case 1: salto(mazmorra, direccion); break;
        case 2: usarEscudo(mazmorra, direccion); break;
        case 3: usarArco(mazmorra, direccion); break;
        case 4: usarBomba(mazmorra); break;
        case 5: usarGancho(mazmorra, direccion); break;
        default: cout << "Opción no válida.\n"; break;
    }
}

void Jugador::interactuar(Mazmorra* mazmorra) {
    int dx = 0, dy = 0;
    if (direccion == "arriba") dy = -1;
    else if (direccion == "abajo") dy = 1;
    else if (direccion == "izquierda") dx = -1;
    else if (direccion == "derecha") dx = 1;

    int cx = x + dx;
    int cy = y + dy;

    char objeto = mazmorra->obtenerCelda(cy, cx);

    switch (objeto) {
        case 'C':
            mazmorra->modificarCelda(cy, cx, 'U');
            abrirCofre();
            recogerLlave();
            break;
        case 'K':
            mazmorra->modificarCelda(cy, cx, 'U');
            abrirCofre();
            recogerLlaveJefe();
            break;
        case 'P':
            if (llaves > 0) {
                mazmorra->modificarCelda(cy, cx, '-');
                abrirPuerta();
            } else {
                cout << "Necesitas una llave para abrir esta puerta.\n";
            }
            break;
        case 'Y':
            if (llavesJefe > 0) {
                mazmorra->modificarCelda(cy, cx, 'T');
                entrarSalaJefe();
            }
            break;
        default:
            cout << "No hay nada con qué interactuar delante de ti.\n";
            break;
    }
}

void Jugador::atacar(Mazmorra* mazmorra) {
    int dx = 0, dy = 0;
    if (direccion == "arriba") dy = -1;
    else if (direccion == "abajo") dy = 1;
    else if (direccion == "izquierda") dx = -1;
    else if (direccion == "derecha") dx = 1;

    int objetivoX = x + dx;
    int objetivoY = y + dy;

    for (auto& enemigo : mazmorra->obtenerEnemigos()) {
        if (enemigo.getX() == objetivoX && enemigo.getY() == objetivoY) {
            enemigo.recibirDano(10);
            cout << "Link ataca con su espada y causa 10 de daño.\n";
            enemigosDerrotados++;
            atacando = true;
            return;
        }
    }

    cout << "No hay enemigo que atacar en esa dirección.\n";
    atacando = false;
}

void Jugador::setPosicion(int nuevoX, int nuevoY) {
    x = nuevoX;
    y = nuevoY;
}

int Jugador::getX() const { return x; }
int Jugador::getY() const { return y; }
int Jugador::getVida() const { return vida; }
string Jugador::getDireccion() const { return direccion; }
void Jugador::setDireccion(const string& nuevaDir) { direccion = nuevaDir; }

void Jugador::recogerLlave() {
    llaves++;
    cout << "Llave recogida! Total de llaves: " << llaves << endl;
}

void Jugador::recogerLlaveJefe() {
    llavesJefe++;
    cout << "Llave de jefe recogida! Total: " << llavesJefe << endl;
}

void Jugador::abrirCofre() {
    cofresAbiertos++;
    cout << "Cofre abierto! Total: " << cofresAbiertos << endl;
}

void Jugador::abrirPuerta() {
    llaves--;
    puertasAbiertas++;
    cout << "Puerta abierta! Llaves restantes: " << llaves << ", Puertas abiertas: " << puertasAbiertas << endl;
}

void Jugador::derrotarEnemigo() {
    enemigosDerrotados++;
    cout << "¡Enemigo derrotado! Total: " << enemigosDerrotados << endl;
    curar(20);
}

void Jugador::entrarSalaJefe() {
    enSalaJefe = true;
    cout << "¡Has entrado a la sala del jefe! Prepárate para la batalla final.\n";
}

void Jugador::ganarJuego() {
    haGanado = true;
    cout << "FELICIDADES!! Has ganado!" << endl;
    cout << "Estadísticas finales:\n";
    cout << "- Pasos dados: " << pasos << endl;
    cout << "- Enemigos derrotados: " << enemigosDerrotados << endl;
    cout << "- Cofres abiertos: " << cofresAbiertos << endl;
    cout << "- Puertas abiertas: " << puertasAbiertas << endl;
    cout << "- Vida final: " << vida << endl;
}

