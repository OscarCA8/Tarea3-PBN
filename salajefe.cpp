#include "salajefe.h"

SalaJefe::SalaJefe(
	int filas,
	int columnas,
	const vector<vector<char>>& mapa,
	const vector<Enemigo>& enemigos,
	const Boss& jefe,
	pair<int, int> entrada
)
	:filas(),
	columnas(),
	mapa(),
	enemigos(),
	jefe(),
	posicionEntradaJefe()
{}

void SalaJefe::mostrarMapa() {

}

void SalaJefe::actualizarMapa() {

}

Boss& SalaJefe::obtenerJefe() {

}

vector<Enemigo>& SalaJefe::obtenerEnemigos() {

}

char SalaJefe::obtenerCelda(int x, int y) const {

}

void SalaJefe::modificarCelda(int x, int y, char simbolo) {

}

pair<int, int> SalaJefe::getEntrada() const {

}

