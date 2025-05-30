#include "enemigo.h"

Enemigo::Enemigo(
	int x, int y,
	int vida,
	int dano,
	int rango,
	int frecuenciaAtaque,
	const vector<pair<int, int>>& patron
)
	:x(x),
	y(y),
	vida(vida),
	dano(dano),
	rango(rango),
	frecuenciaAtaque(frecuenciaAtaque),
	patronMovimiento(patron),
	pasoActual(),
	atacando(),
	xOriginal(x),
	yOriginal(y),
	recibiendoDano(),
	turnosDesdeUltimoAtaque()
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

void Enemigo::recibirDano(int cantidad) {
	vida -= cantidad;
	recibiendoDano = true;
	if (vida < 0) vida = 0;
}

int Enemigo::getX() const {
	return x;
}

int Enemigo::getY() const {
	return y;
}

bool Enemigo::estaPorAtacar() const {
    return turnosDesdeUltimoAtaque >= frecuenciaAtaque;
}

bool Enemigo::estaAtacando() const {
	return atacando;
}

bool Enemigo::estaRecibiendoDano() const {
	return recibiendoDano;
}

int Enemigo::getVida() const {
	return vida;
}

int Enemigo::getDano() const {
	return dano;
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
	recibiendoDano = false;
	turnosDesdeUltimoAtaque = 0;
}

void Enemigo::forceAtk() {
	turnosDesdeUltimoAtaque = frecuenciaAtaque;
	prepararAtaque();
}