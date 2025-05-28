#ifndef JUEGO_H
#define JUEGO_H
#include <string>
using namespace std;

class Juego {
public:
    Juego(const string& dungeonsPath, const string& enemiesPath);
    void iniciar();
};
#endif