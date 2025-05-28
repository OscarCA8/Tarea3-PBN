#include "boss.h"

Boss::Boss(
	const string& nombre, 
	int x, 
	int y, 
	int vida, 
	int daño, 
	int rango, 
	int frecuenciaAtaque,
	const vector<pair<int, int>>& patron
)

	:nombre(nombre), 
	x(x), 
	y(y), 
	vida(vida), 
	daño(daño), 
	rango(rango),
	frecuenciaAtaque(frecuenciaAtaque), 
	patronMovimiento(patron), 
	pasoActual(),
	atacando(), 
	recibiendoDanio(), 
	turnosDesdeUltimoAtaque(),
	xOriginal(x), 
	yOriginal(y) 
{}

void Boss::mover() {
	if (!patronMovimiento.empty()) {
	pasoActual = (pasoActual + 1) % patronMovimiento.size();
	x = xOriginal + patronMovimiento[pasoActual].first;
	y = yOriginal + patronMovimiento[pasoActual].second;
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

void Boss::recibirDaño(int cantidad) {
	vida -= cantidad;
	recibiendoDanio = true;
	if (vida < 0) vida = 0;
}

int Boss::getX() const {
	return x;
}

int Boss::getY() const {
	return y;
}

bool Boss::estaAtacando() const {
	return atacando;
}

bool Boss::estaRecibiendoDaño() const {
	return recibiendoDanio;
}


int Boss::getVida() const {
	return vida;
}

int Boss::getDaño() const {
	return daño;
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
	recibiendoDanio = false;
	turnosDesdeUltimoAtaque = 0;
}

void Boss::forceAtk() {
	turnosDesdeUltimoAtaque = frecuenciaAtaque;
	prepararAtaque();
}


}

