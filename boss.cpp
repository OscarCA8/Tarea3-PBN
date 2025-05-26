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

}

void Boss::prepararAtaque() {

}

void Boss::recibirDaño(int cantidad) {

}

int Boss::getX() const {

}

int Boss::getY() const {

}

bool Boss::estaAtacando() const {

}

bool Boss::estaRecibiendoDaño() const {
 
}

