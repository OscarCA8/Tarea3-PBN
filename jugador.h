#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>
#include "mazmorra.h"
using namespace std;

class Jugador {
private:
    int x, y;
    int vida;
    int dano;
    int rango;
    string habilidad;
    string direccion;
    bool recibiendoDano;
    int llaves;
    int llavesJefe;
    int pasos;
    int cofresAbiertos;
    int puertasAbiertas;
    int enemigosDerrotados;
    int numBombas;
    bool usandoHabilidad;
    bool atacando;
    bool enSalaJefe;
    bool haGanado;

public:
    Jugador(int startX, int startY);

    void mover(char direccionInput, Mazmorra* mazmorra);
    void recibirDano(int cantidad);
    void curar(int cantidad);
    void usarHabilidad(Mazmorra* mazmorra);
    void interactuar(Mazmorra* mazmorra);
    void atacar(Mazmorra* mazmorra);

    int getX() const;
    int getY() const;
    int getVida() const;
    string getDireccion() const;
    void setDireccion(const string& nuevaDir);

    void recogerLlave();
    void recogerLlaveJefe();
    void abrirCofre();
    void abrirPuerta();
    void derrotarEnemigo();

    void entrarSalaJefe();
    void ganarJuego();
};
#endif