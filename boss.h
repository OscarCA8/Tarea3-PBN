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
    int daño;
    int rango;
    int frecuenciaAtaque;
    vector<pair<int, int>> patronMovimiento;
    int pasoActual;
    bool atacando;
    int xOriginal, yOriginal;
    bool recibiendoDaño;
    int turnosDesdeUltimoAtaque;

public:
    Boss(const string& nombre, int x, int y, int vida, int daño, int rango, int frecuenciaAtaque,
         const vector<pair<int, int>>& patron);

    void mover();
    void prepararAtaque();
    void recibirDaño(int cantidad);
    int getX() const;
    int getY() const;
    bool estaAtacando() const;
    bool estaRecibiendoDaño() const;
    int getVida() const;
    int getDaño() const;
    void setVida(int nuevaVida);
    void setPosicion(int nuevaX, int nuevaY);
    void resetear();
    void forceAtk(); 
    
};
#endif