#ifndef JUEGO_H
#define JUEGO_H

#include <string>

#include "mazmorra.h"
#include "salajefe.h"
#include "jugador.h"

using namespace std;

class Juego {
private:
    Mazmorra* mazmorra;
    SalaJefe* salaJefe;
    Jugador* jugador;

public:
    Juego(const string& dungeonsPath, const string& enemiesPath);
    ~Juego();
    void iniciar();
};

#endif