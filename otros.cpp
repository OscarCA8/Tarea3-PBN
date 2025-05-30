#include "otros.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

EnemigosCargados Otros::cargarEnemigosPorIndice(const string& ruta, int indice) {
    EnemigosCargados datos;
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << ruta << endl;
        return datos;
    }

    string linea;
    int actual = 0;
    while (getline(archivo, linea)) {
        if (actual == indice) break;
        actual++;
    }

    if (actual != indice) {
        cerr << "Índice fuera de rango en enemigos.csv\n";
        return datos;
    }

    stringstream ss(linea);
    vector<string> tokens;
    string token;
    while (getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    size_t i = 0;
    while (i < tokens.size() &&
           !((tokens[i][0] >= 'A' && tokens[i][0] <= 'Z') ||
             (tokens[i][0] >= 'a' && tokens[i][0] <= 'z'))) {
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
        enemigo.dano = stoi(tokens[i++]);
        enemigo.rangoAtaque = stoi(tokens[i++]);
        enemigo.frecuenciaAtaque = stoi(tokens[i++]);
        datos.enemigosJefe.push_back(enemigo);
    }

    archivo.close();
    return datos;
}

MazmorrasCargadas Otros::cargarMazmorras(const string& ruta) {
    MazmorrasCargadas resultado;
    ifstream archivo(ruta);

    if (!archivo.is_open()) {
        cerr << "Error: no se pudo abrir el archivo de mazmorras: " << ruta << endl;
        return resultado;
    }

    string linea;
    while (getline(archivo, linea)) { 
        stringstream ss(linea);
        string item;
        vector<string> tokens;

        while (getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        size_t index = 0;
        DataDeMazmorra dm;
        DataDeSaladelJefe ds;

        dm.filas = stoi(tokens[index++]);
        dm.columnas = stoi(tokens[index++]);

        if (index + dm.filas * dm.columnas > tokens.size()) {
            cerr << "Error: datos insuficientes para la mazmorra.\n";
            continue;  
        }

        dm.matriz.resize(dm.filas, vector<char>(dm.columnas));
        for (int i = 0; i < dm.filas; ++i) {
            for (int j = 0; j < dm.columnas; ++j) {
                dm.matriz[i][j] = tokens[index++][0];
            }
        }

        ds.filas = stoi(tokens[index++]);
        ds.columnas = stoi(tokens[index++]);

        if (index + ds.filas * ds.columnas > tokens.size()) {
            cerr << "Error: datos insuficientes para la sala del jefe.\n";
            continue;  
        }

        ds.matriz.resize(ds.filas, vector<char>(ds.columnas));
        for (int i = 0; i < ds.filas; ++i) {
            for (int j = 0; j < ds.columnas; ++j) {
                ds.matriz[i][j] = tokens[index++][0];
            }
        }

        resultado.mazmorras.push_back(dm);
        resultado.salasJefe.push_back(ds);
    }

    archivo.close();
    return resultado;
}