#include "boss.h"

Boss::Boss(
	const string& nombre, 
	int x, 
	int y, 
	int vida, 
	int dano, 
	int rango, 
	int frecuenciaAtaque,
	const vector<pair<int, int>>& patron
)

	:nombre(nombre), 
	x(x), 
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

void Boss::mover() {
	if (!patronMovimiento.empty()) {
	pasoActual = (pasoActual + 1) % patronMovimiento.size();
	x = xOriginal + patronMovimiento[pasoActual].second;
	y = yOriginal + patronMovimiento[pasoActual].first;
	}
}

void Boss::prepararAtaque() {
	turnosDesdeUltimoAtaque++;
	if (turnosDesdeUltimoAtaque >= frecuenciaAtaque) {
	atacando = true;
	turnosDesdeUltimoAtaque = 0;
	} else {
	atacando = false;
	}
}

void Boss::recibirDano(int cantidad) {
	vida -= cantidad;
	recibiendoDano = true;
	if (vida < 0) vida = 0;
}

int Boss::getX() const {
	return x;
}

int Boss::getY() const {
	return y;
}

bool Boss::estaPorAtacar() const {
    return turnosDesdeUltimoAtaque >= frecuenciaAtaque;
}

bool Boss::estaAtacando() const {
	return atacando;
}

bool Boss::estaRecibiendoDano() const {
	return recibiendoDano;
}


int Boss::getVida() const {
	return vida;
}

int Boss::getDano() const {
	return dano;
}

int Boss::getXOriginal() const {
    return xOriginal;
}

int Boss::getYOriginal() const {
    return yOriginal;
}

void Boss::setVida(int nuevaVida) {
	vida = nuevaVida;
}

void Boss::setPosicion(int nuevaX, int nuevaY) {
	x = nuevaX;
	y = nuevaY;
}

void Boss::resetear() {
	x = xOriginal;
	y = yOriginal;
	pasoActual = 0;
	atacando = false;
	recibiendoDano = false;
	turnosDesdeUltimoAtaque = 0;
}

void Boss::forceAtk() {
	turnosDesdeUltimoAtaque = frecuenciaAtaque;
	prepararAtaque();
}
