#include <string>
#include <vector>
#include <utility>
using namespace std;

struct EnemigoData {
    int y;
    int x;
    vector<pair<int, int>> movimientos;
    int vida;
    int daño;
    int rangoAtaque;
    int frecuenciaAtaque;
};

struct BossData {
    string nombre;
    int y;
    int x;
    vector<pair<int, int>> movimientos;
    int vida;
    int daño;
    int rangoAtaque;
    int frecuenciaAtaque;
};

struct MazmorraData {
    int filas;
    int columnas;
    vector<vector<char>> mapa;
};

struct SalaJefeData {
    int filas;
    int columnas;
    vector<vector<char>> mapa;
};

struct EnemigosCargados {
    vector<EnemigoData> enemigosMazmorra;
    BossData jefe;
    vector<EnemigoData> enemigosJefe;
};

struct MazmorrasCargadas {
    vector<MazmorraData> mazmorras;
    vector<SalaJefeData> salasJefe;
};

class Otros {
public:
    EnemigosCargados cargarEnemigos(const string& ruta);
    MazmorrasCargadas cargarMazmorras(const string& ruta);
};