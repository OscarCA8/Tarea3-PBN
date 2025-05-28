#include "salajefe.h"
#include <iostream>

SalaJefe::SalaJefe(
	int filas,
	int columnas,
	const vector<vector<char>>& mapa,
	const vector<Enemigo>& enemigos,
	const Boss& jefe,
	pair<int, int> entrada
)
	:filas(filas),
	columnas(columnas),
	mapa(mapa),
	enemigos(enemigos),
	jefe(jefe),
	posicionEntradaJefe(entrada)
{}

void SalaJefe::mostrarMapa() {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			cout << mapa[i][j];
			if (j < columnas - 1) {
				cout << " ";
			}
		}
		cout << endl;
	}
}

void SalaJefe::actualizarMapa() {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			char celda = mapa[i][j];
			if (celda == 'E' || celda == 'J' || celda == 'L' || celda == 'Z' || 
			    celda == '$' || celda == '!' || celda == 'A' || celda == 'V') {
				mapa[i][j] = '-'; 
			}
		}
	}
	
	for (const auto& enemigo : enemigos) {
		int x = enemigo.getPosicionY();
		int y = enemigo.getPosicionX();
		
		if (x >= 0 && x < filas && y >= 0 && y < columnas) {
			char simbolo = 'E';
			if (enemigo.estaRecibiendoDaño()) {
				simbolo = '$'; 
			} else if (enemigo.estaAtacando()) {
				simbolo = 'A'; 
			} else if (enemigo.estaPorAtacar()) {
				simbolo = '!';
			}
			
			mapa[x][y] = simbolo;
		}
	}
	
	int jefeX = jefe.getPosicionY(); 
	int jefeY = jefe.getPosicionX(); 
	
	if (jefeX >= 0 && jefeX < filas && jefeY >= 0 && jefeY < columnas) {
		char simboloJefe = 'J'; 
		
		if (jefe.estaRecibiendoDaño()) {
			simboloJefe = '$'; 
		} else if (jefe.estaAtacando()) {
			simboloJefe = 'A'; 
		} else if (jefe.estaPorAtacar()) {
			simboloJefe = '!'; 
		}
		
		mapa[jefeX][jefeY] = simboloJefe;
	}
	
	if (jefe.getVida() <= 0) {
		int jefeOriginalX = jefe.getYOriginal();
		int jefeOriginalY = jefe.getXOriginal();
		if (jefeOriginalX >= 0 && jefeOriginalX < filas && 
		    jefeOriginalY >= 0 && jefeOriginalY < columnas) {
			mapa[jefeOriginalX][jefeOriginalY] = 'V'; 
		}
	}
}

Boss& SalaJefe::obtenerJefe() {
	return jefe;
}

vector<Enemigo>& SalaJefe::obtenerEnemigos() {
	return enemigos;
}

char SalaJefe::obtenerCelda(int x, int y) const {
	if (x >= 0 && x < filas && y >= 0 && y < columnas) {
		return mapa[x][y];
	}
	return 'X';
}

void SalaJefe::modificarCelda(int x, int y, char simbolo) {
	if (x >= 0 && x < filas && y >= 0 && y < columnas) {
		mapa[x][y] = simbolo;
	}
}

pair<int, int> SalaJefe::getEntrada() const {
	return PosicionEntradaJefe;
}

