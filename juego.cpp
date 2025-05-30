#include "juego.h"
#include "mazmorra.h"
#include "enemigo.h"
#include "jugador.h"
#include "boss.h"
#include "salajefe.h"
#include "otros.h"
#include <iostream>
using namespace std;

Juego::Juego(const string& dungeonsPath, const string& enemiesPath) {
    mazmorra = nullptr;
    salaJefe = nullptr;
    jugador = nullptr;

    Otros lector;
    MazmorrasCargadas datosMazmorras = lector.cargarMazmorras(dungeonsPath);

    if (datosMazmorras.mazmorras.empty()) {
        cerr << "No hay mazmorras cargadas\n";
        return;
    }

    cout << "Seleccione una mazmorra:\n";
    for (size_t i = 0; i < datosMazmorras.mazmorras.size(); ++i) {
        cout << i << ": Mazmorra " << i << " (" << datosMazmorras.mazmorras[i].filas
                  << "x" << datosMazmorras.mazmorras[i].columnas << ")\n";
    }

    int opcion;
    cin >> opcion;
    if (opcion < 0 || opcion >= static_cast<int>(datosMazmorras.mazmorras.size())) {
        cerr << "Opción inválida\n";
        exit(1); 
    }

    EnemigosCargados datosEnemigos = lector.cargarEnemigosPorIndice(enemiesPath, opcion);

    const DataDeMazmorra& datosMapa = datosMazmorras.mazmorras[opcion];
    mazmorra = new Mazmorra(datosMapa.filas, datosMapa.columnas, datosMapa.matriz);
    for (const auto& d : datosEnemigos.enemigosMazmorra) {
        Enemigo e(d.x, d.y, d.vida, d.dano, d.rangoAtaque, d.frecuenciaAtaque, d.movimientos);
        mazmorra->obtenerEnemigos().push_back(e);
    }

    const DataDeSaladelJefe& salaData = datosMazmorras.salasJefe[opcion];
    const DataDelBoss& dBoss = datosEnemigos.jefe;
    Boss boss(dBoss.nombre, dBoss.x, dBoss.y, dBoss.vida, dBoss.dano,
              dBoss.rangoAtaque, dBoss.frecuenciaAtaque, dBoss.movimientos);
    vector<Enemigo> enemigosJefe;
    for (const auto& d : datosEnemigos.enemigosJefe) {
        enemigosJefe.emplace_back(d.x, d.y, d.vida, d.dano, d.rangoAtaque, d.frecuenciaAtaque, d.movimientos);
    }
    salaJefe = new SalaJefe(salaData.filas, salaData.columnas, salaData.matriz,
                            enemigosJefe, boss, make_pair(dBoss.x, dBoss.y));

    jugador = new Jugador(1, 1);
}

Juego::~Juego() {
    delete mazmorra;
    delete salaJefe;
    delete jugador;
}

void Juego::iniciar() {
    bool enSalaJefe = false;
    bool juegoTerminado = false;

    while (!juegoTerminado) {
        if (!enSalaJefe) {
            mazmorra->actualizarMapa();
            mazmorra->modificarCelda(jugador->getY(), jugador->getX(), 'L');
            mazmorra->mostrarMapa();
        } else {
            salaJefe->actualizarMapa();
            mazmorra->modificarCelda(jugador->getY(), jugador->getX(), 'L');
            salaJefe->mostrarMapa();
        }

        cout << "\nVida: " << jugador->getVida() << ". Comandos: w/a/s/d=mover, x=atacar, z=habilidad, c=interactuar, p=salir\n> ";
	char comando;
	cin >> comando;

	switch (comando) {
	    case 'w': case 'a': case 's': case 'd':
		jugador->mover(comando, enSalaJefe ? static_cast<Mazmorra*>(salaJefe) : mazmorra);
		break;
	    case 'x':
		jugador->atacar(enSalaJefe ? static_cast<Mazmorra*>(salaJefe) : mazmorra);
		break;
	    case 'z':
		jugador->usarHabilidad(enSalaJefe ? static_cast<Mazmorra*>(salaJefe) : mazmorra);
		break;
	    case 'c':
		jugador->interactuar(enSalaJefe ? static_cast<Mazmorra*>(salaJefe) : mazmorra);
		break;
	    case 'p':
		cout << "Juego terminado por el jugador.\n";
		juegoTerminado = true;
		break;
		return;
	    default:
		cout << "Comando no reconocido.\n";
	}

        if (!enSalaJefe) {
            for (auto& enemigo : mazmorra->obtenerEnemigos()) {
                enemigo.mover();
                enemigo.prepararAtaque();
                if (enemigo.estaAtacando() &&
                    (enemigo.getX() - jugador->getX()) * (enemigo.getX() - jugador->getX()) <= 1 &&
                    (enemigo.getY() - jugador->getY()) * (enemigo.getY() - jugador->getY()) <= 1) {
                    jugador->recibirDano(enemigo.getDano());
                }
            }

            char celda = mazmorra->obtenerCelda(jugador->getY(), jugador->getX());
            if (celda == 'T') {
                jugador->entrarSalaJefe();
                enSalaJefe = true;
                cout << "Transición a sala del jefe...\n";
            }

        } else {
            for (auto& enemigo : salaJefe->obtenerEnemigos()) {
                enemigo.mover();
                enemigo.prepararAtaque();
                if (enemigo.estaAtacando() &&
                    (enemigo.getX() - jugador->getX()) * (enemigo.getX() - jugador->getX()) <= 1 &&
                    (enemigo.getY() - jugador->getY()) * (enemigo.getY() - jugador->getY()) <= 1) {
                    jugador->recibirDano(enemigo.getDano());
                }
            }

            Boss& jefe = salaJefe->obtenerJefe();
            jefe.mover();
            jefe.prepararAtaque();
            if (jefe.estaAtacando() &&
                (jefe.getX() - jugador->getX()) * (jefe.getX() - jugador->getX()) <= 1 &&
                (jefe.getY() - jugador->getY()) * (jefe.getY() - jugador->getY()) <= 1) {
                jugador->recibirDano(jefe.getDano());
            }

            if (jefe.getVida() <= 0) {
                jugador->ganarJuego();
                juegoTerminado = true;
            }
        }

        if (jugador->getVida() <= 0) {
            cout << "Link ha caído. Fin del juego.\n";
            juegoTerminado = true;
        }
    }
}
