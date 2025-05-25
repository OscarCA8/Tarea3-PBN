#include <vector>
#include <string>
#include "Enemigo.hpp"
#include "Boss.hpp"
using namespace std;

class SalaJefe {
private:
    int filas;
    int columnas;
    vector<vector<char>> mapa;
    vector<Enemigo> enemigos;
    Boss jefe;
    pair<int, int> posicionEntradaJefe;

public:
    SalaJefe(int filas, int columnas, const vector<vector<char>>& mapa,
             const vector<Enemigo>& enemigos, const Boss& jefe, pair<int, int> entrada);

    void mostrarMapa();
    void actualizarMapa();
    Boss& obtenerJefe();
    vector<Enemigo>& obtenerEnemigos();
    char obtenerCelda(int x, int y) const;
    void modificarCelda(int x, int y, char simbolo);
    pair<int, int> getEntrada() const;
};
