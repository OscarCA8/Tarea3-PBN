#ifndef boss_h
#define boss_h
#include <string>
#include <vector>
#include <utility>
using namespace std;

class Boss {
private:
    string nombre;
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
    Boss(const string& nombre, int x, int y, int vida, int dano, int rango, int frecuenciaAtaque,
         const vector<pair<int, int>>& patron);

    void mover();
    void prepararAtaque();
    void recibirDano(int cantidad);
    int getX() const;
    int getY() const;
    int getXOriginal() const;
    int getYOriginal() const;
    bool estaAtacando() const;
    bool estaRecibiendoDano() const;
    bool estaPorAtacar() const;
    int getVida() const;
    int getDano() const;
    void setVida(int nuevaVida);
    void setPosicion(int nuevaX, int nuevaY);
    void resetear();
    void forceAtk(); 
    
};
#endif