#include <string>
using namespace std;

class Jugador {
private:
    int x, y;
    int vida;
    int daño;
    int rango;
    string habilidad;
    string direccion;
    bool recibiendoDaño;
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

    void mover(char direccionInput);
    void recibirDaño(int cantidad);
    void curar(int cantidad);
    void usarHabilidad();
    void atacar();

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