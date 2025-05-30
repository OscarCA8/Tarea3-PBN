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
        celdaDestino == 'K' || celdaDestino == 'Y' || celdaDestino == 'E' || celdaDestino == 'J' || celdaDestino == 'U' || celdaDestino == 'A') {
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
    
    if (vida < 0) {
        vida = 0;
    }
    
    cout << "Link recibió " << cantidad << " puntos de daño! Vida restante: " << vida << endl;
    
    if (vida == 0) {
        cout << "Link ha sido derrotado!" << endl;
    }
    
    recibiendoDano = false;
}

void Jugador::curar(int cantidad) {
    if (cantidad <= 0) return;
    
    vida += cantidad;
    if (vida > 100) {
        vida = 100;
    }
    
    cout << "Link se curó " << cantidad << " puntos de vida. Vida actual: " << vida << endl;
}

void Jugador::salto(Mazmorra* mazmorra, char direccion) {
    int dx = 0, dy = 0;
    if (direccion == 'w') dy = -2;   
    else if (direccion == 'a') dx = -2;  
    else if (direccion == 's') dy = 2;   
    else if (direccion == 'd') dx = 2;   

    char celdaDestino = mazmorra->obtenerCelda(y + dy, x + dx);
    if (celdaDestino == '-' || celdaDestino == ' ') {
        setPosicion(y + dy, x + dx);
    } else {
        cout << "¡Hay un obstáculo! Perdiste el turno." << endl;
    }
}

void Jugador::usarEscudo(Mazmorra* mazmorra, char direccion) {
    int index = 0;
   
    if (direccion == 'N') {
        index = 0;  
    } else if (direccion == 'S') {
        index = 1;  
    } else if (direccion == 'E') {
        index = 2;  
    } else if (direccion == 'O') {
        index = 3;  
    }
    
    if (enemigosQueAtacan[index]) {
        cout << "Escudo activado contra ataque en " << direccion << endl;
    } else {
        cout << "No hay enemigos atacando en " << direccion << endl;
    }
}

void Jugador::usarArco(Mazmorra* mazmorra, char direccion) {
    int startX = x, startY = y;
    int range = 5; 
    for (int i = startX - range / 2; i < startX + range / 2; ++i) {
        for (int j = startY - range / 2; j < startY + range / 2; ++j) {
            if (mazmorra->obtenerCelda(i, j) != 'X' && 
                mazmorra->obtenerCelda(i, j) != '-') { 
                for (auto& enemigo : mazmorra->obtenerEnemigos()) {
                    if (enemigo.getX() == i && enemigo.getY() == j) {
                        enemigo.recibirDano(10);
                    }
                }
            }
        }
    }
}

void Jugador::usarBomba(Mazmorra* mazmorra) {
    if (numBombas > 0) {
        char celdaDestino = mazmorra->obtenerCelda(y + 1, x); 
        if (celdaDestino == 'X') { 
            mazmorra->modificarCelda(y + 1, x, '-'); 
        }

        for (auto& enemigo : mazmorra->obtenerEnemigos()) {
            if (abs(enemigo.getX() - x) <= 1 && abs(enemigo.getY() - y) <= 1) {
                enemigo.recibirDano(100);
            }
        }

        numBombas--;
        cout << "¡Bomba activada!" << endl;
    } else {
        cout << "No tienes bombas disponibles." << endl;
    }
}

void Jugador::usarGancho(Mazmorra* mazmorra, char direccion) {
    int dx = 0, dy = 0;
    if (direccion == 'w') dy = -1; 
    else if (direccion == 'a') dx = -1; 
    else if (direccion == 's') dy = 1; 
    else if (direccion == 'd') dx = 1; 

    char celda = mazmorra->obtenerCelda(y + dy, x + dx);
    if (celda == 'X' || celda == 'C' || celda == 'K') {
        setPosicion(y + dy, x + dx);
        for (auto& enemigo : mazmorra->obtenerEnemigos()) {
            if (enemigo.getX() == x + dx && enemigo.getY() == y + dy) {
                enemigo.recibirDano(5);
            }
        }
    } else {
        cout << "No puedes usar el gancho aquí." << endl;
    }
}


void Jugador::usarHabilidad(Mazmorra* mazmorra) {
    cout << "Selecciona una habilidad:" << endl;
    cout << "1. Salto" << endl;
    cout << "2. Escudo" << endl;
    cout << "3. Arco" << endl;
    cout << "4. Bomba" << endl;
    cout << "5. Gancho" << endl;
    
    int opcion;
    cin >> opcion;  
    
    char direccion; 
    
    switch (opcion) {
        case 1: 
            cout << "Indica la dirección (w: arriba, a: izquierda, s: abajo, d: derecha): ";
            cin >> direccion;
            salto(mazmorra, direccion);
            break;
        case 2: 
            cout << "Indica la dirección (w: arriba, a: izquierda, s: abajo, d: derecha): ";
            cin >> direccion;
            usarEscudo(mazmorra, direccion); 
            break;
        case 3: 
            cout << "Indica la dirección (w: arriba, a: izquierda, s: abajo, d: derecha): ";
            cin >> direccion;
            usarArco(mazmorra, direccion); 
            break;
        case 4: 
            usarBomba(mazmorra); 
            break;
        case 5: 
            cout << "Indica la dirección (w: arriba, a: izquierda, s: abajo, d: derecha): ";
            cin >> direccion;
            usarGancho(mazmorra, direccion); 
            break;
        default:
            cout << "Opción no válida. Intenta de nuevo." << endl;
            break;
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

    switch(objeto) {
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
                cout << "Necesitas una llave para abrir esta puerta." << endl;
            }
            break;

        case 'Y': 
            if (llavesJefe > 0) {
                mazmorra->modificarCelda(cy, cx, 'T');
                entrarSalaJefe();
            }
            break;

        default:
            cout << "No hay nada con qué interactuar delante de ti." << endl;
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

    char celda = mazmorra->obtenerCelda(objetivoX, objetivoY);

    if (celda == 'E' || celda == 'A' || celda == '!' || celda == '$') {
        mazmorra->modificarCelda(objetivoX, objetivoY, '$');
        cout << "Link ataca al enemigo con su espada y causa 10 de daño.\n";
        enemigosDerrotados++; 
    } else {
        cout << "No hay enemigo que atacar en esa dirección.\n";
    }
    atacando = true;
}

void Jugador::setPosicion(int nuevoX, int nuevoY) {
    x = nuevoX;
    y = nuevoY;
}

int Jugador::getX() const {
    return x;
}

int Jugador::getY() const {
    return y;
}

int Jugador::getVida() const {
    return vida;
}

string Jugador::getDireccion() const {
    return direccion;
}

void Jugador::setDireccion(const string& nuevaDir) {
    direccion = nuevaDir;
}

void Jugador::recogerLlave() {
    llaves++;
    cout << "Llave recogida! Total de llaves: " << llaves << endl;
}

void Jugador::recogerLlaveJefe() {
    llavesJefe++;
    cout << "Llave de jefe recogida! Total de llaves de jefe: " << llavesJefe << endl;
}

void Jugador::abrirCofre() {
    cofresAbiertos++;
    cout << "Cofre abierto! Total de cofres abiertos: " << cofresAbiertos << endl;
}

void Jugador::abrirPuerta() {
    if (llaves > 0) {
        llaves--;
        puertasAbiertas++;
        cout << "Puerta abierta! Llaves restantes: " << llaves << ", Puertas abiertas: " << puertasAbiertas << endl;
    } else {
        cout << "No tienes llaves para abrir la puerta." << endl;
    }
}

void Jugador::derrotarEnemigo() {
    enemigosDerrotados++;
    cout << "¡Enemigo derrotado! Total de enemigos derrotados: " << enemigosDerrotados << endl;
    curar(20);
}

void Jugador::entrarSalaJefe() {
    if (llavesJefe > 0) {
        enSalaJefe = true;
        cout << "¡Has entrado a la sala del jefe! Prepárate para la batalla final." << endl;
    } else {
        cout << "Necesitas una llave de jefe para entrar a esta sala." << endl;
    }
}

void Jugador::ganarJuego() {
    haGanado = true;
    cout << "FELICIDADES!! Has ganado!" << endl;
    cout << "Estadísticas finales:" << endl;
    cout << "- Pasos dados: " << pasos << endl;
    cout << "- Enemigos derrotados: " << enemigosDerrotados << endl;
    cout << "- Cofres abiertos: " << cofresAbiertos << endl;
    cout << "- Puertas abiertas: " << puertasAbiertas << endl;
    cout << "- Vida final: " << vida << endl;

}