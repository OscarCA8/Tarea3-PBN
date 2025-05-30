#ifndef MAZMORRA_H
#define MAZMORRA_H
#include <vector>
#include <string>
#include "enemigo.h"
using namespace std;

class Mazmorra {
private:
    int filas;
    int columnas;
    vector<vector<char>> mapa;
    vector<Enemigo> enemigos;

public:
    Mazmorra(int filas, int columnas, const vector<vector<char>>& mapa);

    void mostrarMapa();
    void actualizarMapa();
    char obtenerCelda(int x, int y) const;
    void modificarCelda(int x, int y, char simbolo);
    bool puertaJefeAbierta();

    vector<Enemigo>& obtenerEnemigos();
    int getFilas() const;
    int getColumnas() const;
};
#endif