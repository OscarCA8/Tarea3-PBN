#include "mazmorra.h"
#include <iostream>
Mazmorra::Mazmorra(
	int filas, 
	int columnas, 
	const vector<vector<char>>& mapa
)
	:filas(filas), 
	columnas(columnas), 
	mapa(mapa), 
	enemigos()
{}

void Mazmorra::mostrarMapa() {
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

void Mazmorra::actualizarMapa() {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			char celda = mapa[i][j];
			if (celda == 'E' || celda == 'L' || celda == 'Z' || 
			    celda == '$' || celda == '!' || celda == 'A') {
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
}

char Mazmorra::obtenerCelda(int x, int y) const {
	if (x >= 0 && x < filas && y >= 0 && y < columnas) {
		return mapa[x][y];
	}
	return 'X';
}

void Mazmorra::modificarCelda(int x, int y, char simbolo) {
	if (x >= 0 && x < filas && y >= 0 && y < columnas) {
		mapa[x][y] = simbolo;
	}
}

vector<Enemigo>& Mazmorra::obtenerEnemigos() {
	return enemigos;
}

int Mazmorra::getFilas() const {
	return filas;
}

int Mazmorra::getColumnas() const {
	return columnas;
}

