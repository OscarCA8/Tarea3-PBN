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
        celdaDestino == 'K' || celdaDestino == 'Y' || celdaDestino == 'E' || celdaDestino == 'J') {
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

void Jugador::usarHabilidad(Mazmorra* mazmorra) {
    cout << "Link usa su habilidad especial: lanza una bomba.\n";
    usandoHabilidad = true;

    // Simulación: marca las 4 direcciones como daño si hay enemigos o paredes rompibles
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        char celda = mazmorra->obtenerCelda(nx, ny);

        if (celda == 'E' || celda == 'A' || celda == '!' || celda == '$' || celda == 'X') {
            mazmorra->modificarCelda(nx, ny, '$');
        }
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
        enemigosDerrotados++; // Aquí idealmente deberías reducir vida real al enemigo
    } else {
        cout << "No hay enemigo que atacar en esa dirección.\n";
    }
    atacando = true;
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