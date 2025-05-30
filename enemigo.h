#ifndef ENEMIGO_H
#define ENEMIGO_H
#include <vector>
#include <utility>
using namespace std;

class Enemigo {
private:
    int x, y;
    int vida;
    int dano;
    int rango;
    int frecuenciaAtaque;
    vector<pair<int, int>> patronMovimiento;
    int pasoActual;
    bool atacando;
    int xOriginal, yOriginal;
    bool recibiendoDano;
    int turnosDesdeUltimoAtaque;

public:
    Enemigo(int x, int y, int vida, int dano, int rango, int frecuenciaAtaque,
            const vector<pair<int, int>>& patron);

    void mover();
    void prepararAtaque();
    void recibirDano(int cantidad);
    int getX() const;
    int getY() const;
    bool estaAtacando() const;
    bool estaRecibiendoDano() const;
    bool estaPorAtacar() const;
    int getVida() const;
    int getDano() const;
    void setVida(int nuevaVida);
    void setPosicion(int nuevaX, int nuevaY);
    void resetear();
    void forceAtk();
    void reiniciarEstadoDano(); 
};
#endif
