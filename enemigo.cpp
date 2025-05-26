#include "enemigo.h"

Enemigo::Enemigo(
	int x, int y,
	int vida,
	int daño,
	int rango,
	int frecuenciaAtaque,
	const vector<pair<int, int>>& patron
)
	:x(x),
	y(y),
	vida(vida),
	daño(daño),
	rango(rango),
	frecuenciaAtaque(frecuenciaAtaque),
	patronMovimiento(patron),
	pasoActual(),
	atacando(),
	recibiendoDaño(),
	turnosDesdeUltimoAtaque(),
	xOriginal(x),
	yOriginal(y)
{}

void Enemigo::mover() {

}

void Enemigo::prepararAtaque() {

}

void Enemigo::recibirDaño(int cantidad) {

}

int Enemigo::getX() const {

}

int Enemigo::getY() const {

}

bool Enemigo::estaAtacando() const {

}

bool Enemigo::estaRecibiendoDaño() const {

}

