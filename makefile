CC=g++
FLAGS=-Wall -Wextra -Wundef -Werror -Wuninitialized -Winit-self
EXE=tarea3

ARCHIVOS=main.o jugador.o enemigo.o boss.o mazmorra.o salajefe.o juego.o otros.o

$(EXE): $(OBJS)
	$(CC) $(FLAGS) $(ARCHIVOS) -o $(EXE)

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp -o main.o

Jugador.o: jugador.cpp jugador.h
	$(CC) $(FLAGS) -c jugador.cpp -o jugador.o

Enemigo.o: enemigo.cpp enemigo.h
	$(CC) $(FLAGS) -c enemigo.cpp -o enemigo.o

Boss.o: boss.cpp boss.h
	$(CC) $(FLAGS) -c boss.cpp -o boss.o

Mazmorra.o: mazmorra.cpp mazmorra.h
	$(CC) $(FLAGS) -c mazmorra.cpp -o mazmorra.o

SalaJefe.o: salajefe.cpp salajefe.h
	$(CC) $(FLAGS) -c salajefe.cpp -o salajefe.o

Juego.o: juego.cpp juego.h
	$(CC) $(FLAGS) -c juego.cpp -o juego.o

Otros.o: otros.cpp otros.h
	$(CC) $(FLAGS) -c otros.cpp -o otros.o

run: $(EXE)
	./$(EXE)

all: clean run

clean:
	rm -f $(EXE) *.o