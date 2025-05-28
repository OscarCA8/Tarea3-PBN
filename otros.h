#ifndef OTROS_H
#define OTROS_H
#include <string>
#include <vector>
#include <utility>
using namespace std;

struct DataDelEnemigo {
    int y;
    int x;
    vector<pair<int, int>> movimientos;
    int vida;
    int daño;
    int rangoAtaque;
    int frecuenciaAtaque;
};

struct DataDelBoss {
    string nombre;
    int y;
    int x;
    vector<pair<int, int>> movimientos;
    int vida;
    int daño;
    int rangoAtaque;
    int frecuenciaAtaque;
};

struct DataDeMazmorra {
    int filas;
    int columnas;
    vector<vector<char>> mapa;
};

struct DataDeSaladelJefe {
    int filas;
    int columnas;
    vector<vector<char>> mapa;
};

struct EnemigosCargados {
    vector<DataDelEnemigo> enemigosMazmorra;
    DataDelBoss jefe;
    vector<DataDelEnemigo> enemigosJefe;
};

struct MazmorrasCargadas {
    vector<DataDeMazmorra> mazmorras;
    vector<DataDeSaladelJefe> salasJefe;
};

class Otros {
public:
    EnemigosCargados cargarEnemigos(const string& ruta);
    MazmorrasCargadas cargarMazmorras(const string& ruta);
};
#endif