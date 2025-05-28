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
	if (!patronMovimiento.empty()) {
	pasoActual = (pasoActual + 1) % patronMovimiento.size();
	x = xOriginal + patronMovimiento[pasoActual].first;
	y = yOriginal + patronMovimiento[pasoActual].second;
	}
}

void Enemigo::prepararAtaque() {
	turnosDesdeUltimoAtaque++;
	if (turnosDesdeUltimoAtaque >= frecuenciaAtaque) {
	atacando = true;
	turnosDesdeUltimoAtaque = 0;
	} else {
	atacando = false;
	}
}

void Enemigo::recibirDaño(int cantidad) {
	vida -= cantidad;
	recibiendoDaño = true;
	if (vida < 0) vida = 0;
}

int Enemigo::getX() const {
	return x;
}

int Enemigo::getY() const {
	return y;
}

bool Enemigo::estaAtacando() const {
	return atacando;
}

bool Enemigo::estaRecibiendoDaño() const {
	return recibiendoDaño;
}

int Enemigo::getVida() const {
	return vida;
}

int Enemigo::getDaño() const {
	return daño;
}

void Enemigo::setVida(int nuevaVida) {
	vida = nuevaVida;
}

void Enemigo::setPosicion(int nuevaX, int nuevaY) {
	x = nuevaX;
	y = nuevaY;
}

void Enemigo::resetear() {
	x = xOriginal;
	y = yOriginal;
	pasoActual = 0;
	atacando = false;
	recibiendoDalo = false;
	turnosDesdeUltimoAtaque = 0;
}

void Enemigo::forceAtk() {
	turnosDesdeUltimoAtaque = frecuenciaAtaque;
	prepararAtaque();
}


