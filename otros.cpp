#include "otros.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>

using namespace std;



EnemigosCargados Otros::cargarEnemigos(const string& ruta) {
	EnemigosCargados datos;
	ifstream archivo(ruta);
	if (!archivo.is_open()) {
		cerr << "Error al abrir el archivo: " << ruta << endl;
		return datos;
	}

	string linea;
	while (getline(archivo, linea)) {
		stringstream ss(linea);
		vector<string> tokens;
		string token;

		// Separar todos los tokens por coma
		while (getline(ss, token, ',')) {
			tokens.push_back(token);
		}

		size_t i = 0;
		// --- Leer enemigos de mazmorra ---
		while (i < tokens.size() && !isalpha(tokens[i][0])) {
			DataDelEnemigo enemigo;
			enemigo.y = stoi(tokens[i++]);
			enemigo.x = stoi(tokens[i++]);
			int numMov = stoi(tokens[i++]);
			for (int j = 0; j < numMov; ++j) {
				int dx = stoi(tokens[i++]);
				int dy = stoi(tokens[i++]);
				enemigo.movimientos.push_back({dx, dy});
			}
			enemigo.vida = stoi(tokens[i++]);
			enemigo.dano = stoi(tokens[i++]);
			enemigo.rangoAtaque = stoi(tokens[i++]);
			enemigo.frecuenciaAtaque = stoi(tokens[i++]);
			datos.enemigosMazmorra.push_back(enemigo);
		}

		// --- Leer jefe ---
		DataDelBoss jefe;
		jefe.nombre = tokens[i++];
		jefe.y = stoi(tokens[i++]);
		jefe.x = stoi(tokens[i++]);
		int numMov = stoi(tokens[i++]);
		for (int j = 0; j < numMov; ++j) {
			int dx = stoi(tokens[i++]);
			int dy = stoi(tokens[i++]);
			jefe.movimientos.push_back({dx, dy});
		}
		jefe.vida = stoi(tokens[i++]);
		jefe.dano = stoi(tokens[i++]);
		jefe.rangoAtaque = stoi(tokens[i++]);
		jefe.frecuenciaAtaque = stoi(tokens[i++]);
		datos.jefe = jefe;

		// --- Leer enemigos de sala del jefe ---
		while (i < tokens.size()) {
			DataDelEnemigo enemigo;
			enemigo.y = stoi(tokens[i++]);
			enemigo.x = stoi(tokens[i++]);
			int numMov = stoi(tokens[i++]);
			for (int j = 0; j < numMov; ++j) {
				int dx = stoi(tokens[i++]);
				int dy = stoi(tokens[i++]);
				enemigo.movimientos.push_back({dx, dy});
			}
			 enemigo.vida = stoi(tokens[i++]);
			enemigo.dano = stoi(tokens[i++]);using namespace std;
			enemigo.rangoAtaque = stoi(tokens[i++]);
			enemigo.frecuenciaAtaque = stoi(tokens[i++]);
			datos.enemigosJefe.push_back(enemigo);
		}
	}

	archivo.close();
	return datos;
}


MazmorrasCargadas Otros::cargarMazmorras(const string& ruta) {
    MazmorrasCargadas cargadas;
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo de mazmorras: " << ruta << endl;
        return cargadas;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        int i = 0;
        // Mazmorra
        int filasM = stoi(tokens[i++]);
        int columnasM = stoi(tokens[i++]);
        DataDeMazmorra mazmorra;
        mazmorra.filas = filasM;
        mazmorra.columnas = columnasM;
        mazmorra.matriz.resize(filasM, vector<char>(columnasM));

        for (int f = 0; f < filasM; ++f) {
            for (int c = 0; c < columnasM; ++c) {
                mazmorra.matriz[f][c] = tokens[i++][0];
            }
        }
        cargadas.mazmorras.push_back(mazmorra);

        // Sala del Jefe
        int filasS = stoi(tokens[i++]);
        int columnasS = stoi(tokens[i++]);
        DataDeSaladelJefe sala;
        sala.filas = filasS;
        sala.columnas = columnasS;
        sala.matriz.resize(filasS, vector<char>(columnasS));

        for (int f = 0; f < filasS; ++f) {
            for (int c = 0; c < columnasS; ++c) {
                sala.matriz[f][c] = tokens[i++][0];
            }
        }
        cargadas.salasJefe.push_back(sala);
    }

    archivo.close();
    return cargadas;
}



