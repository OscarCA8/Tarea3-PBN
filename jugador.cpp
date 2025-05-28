#include <iostream>
#include "jugador.h"
using namespace std;

Jugador::Jugador(int startX, int startY) {
    x = startX;
    y = startY;
    vida = 100;        
    daño = 20;         
    rango = 1;         
    habilidad = "";    
    direccion = "arriba"; 
    recibiendoDaño = false;
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

void Jugador::mover(char direccionInput) {
    string nuevaDireccion;
    
    switch(direccionInput) {
        case 'w':
        case 'W':
            nuevaDireccion = "arriba";
            break;
        case 's':
        case 'S':
            nuevaDireccion = "abajo";
            break;
        case 'a':
        case 'A':
            nuevaDireccion = "izquierda";
            break;
        case 'd':
        case 'D':
            nuevaDireccion = "derecha";
            break;
        default:
            cout << "dirección no válida. Use W/A/S/D." << endl;
            return;
    }
    

    if (direccion != nuevaDireccion) {
        direccion = nuevaDireccion;
        cout << "Link gira hacia " << direccion << endl;
        return; 
    }
    
    int nuevaX = x, nuevaY = y;
    switch(direccionInput) {
        case 'w':
        case 'W':
            nuevaY--;
            break;
        case 's':
        case 'S':
            nuevaY++;
            break;
        case 'a':
        case 'A':
            nuevaX--;
            break;
        case 'd':
        case 'D':
            nuevaX++;
            break;
    }
    
    x = nuevaX;
    y = nuevaY;
    pasos++;
    cout << "Link se movió hacia " << direccion << ". Posición: (" << x << ", " << y << ")" << endl;
}

void Jugador::recibirDaño(int cantidad) {
    if (cantidad <= 0) return;
    
    recibiendoDaño = true;
    vida -= cantidad;
    
    if (vida < 0) {
        vida = 0;
    }
    
    cout << "Link recibió " << cantidad << " puntos de daño! Vida restante: " << vida << endl;
    
    if (vida == 0) {
        cout << "Link ha sido derrotado!" << endl;
    }
    
    recibiendoDaño = false;
}

void Jugador::curar(int cantidad) {
    if (cantidad <= 0) return;
    
    vida += cantidad;
    if (vida > 100) {
        vida = 100;
    }
    
    cout << "Link se curó " << cantidad << " puntos de vida. Vida actual: " << vida << endl;
}

void Jugador::usarHabilidad() {

}

void Jugador::atacar() {
    atacando = true;
    cout << "Link ataca hacia " << direccion << " con su espada (10 de daño)!" << endl;
    atacando = false;
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
