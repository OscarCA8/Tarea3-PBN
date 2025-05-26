#include "jugador.h"

Jugador::Jugador(
	int startX, 
	int startY
)
	:x(),
	y(),
	vida(),
	daño(),
	rango(),
	habilidad(),
	direccion(),
	recibiendoDaño(),
	llaves(),
	llavesJefe(),
	pasos(),
	cofresAbiertos(),
	puertasAbiertas(),
	enemigosDerrotados(),
	numBombas(),
	usandoHabilidad(),
	atacando(),
	enSalaJefe(),
	haGanado()
{}

void Jugador::mover(char direccionInput) {

}

void Jugador::recibirDanio(int cantidad) {

}

void Jugador::curar(int cantidad) {

}

void Jugador::usarHabilidad() {

}

void Jugador::atacar() {

}

int Jugador::getX() const {

}

int Jugador::getY() const {

}

int Jugador::getVida() const {

}

string Jugador::getDireccion() const {

}

void Jugador::setDireccion(const string& nuevaDir) {

}

void Jugador::recogerLlave() {

}

void Jugador::recogerLlaveJefe() {

}

void Jugador::abrirCofre() {

}

void Jugador::abrirPuerta() {

}

void Jugador::derrotarEnemigo() {

}

void Jugador::entrarSalaJefe() {

}

void Jugador::ganarJuego() {

}

