#include <string>
#include <iostream>
#include "juego.h"

int main(int argc, char* argv[]) {
	std::string dungeonsPath = "mazmorras.csv";
	std::string enemiesPath = "enemigos.csv";

	if (argc >= 3) {
	dungeonsPath = argv[1];
	enemiesPath = argv[2];
	}

	try {
	Juego juego(dungeonsPath, enemiesPath);
	juego.iniciar();
	} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << std::endl;
	return 1;
	}

	return 0;
}
