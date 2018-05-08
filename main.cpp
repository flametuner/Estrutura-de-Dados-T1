#include <iostream>
#include <stdlib.h>
#include "semaphore.h"
#include "vehicle.h"
#include "track_queue.cpp"
#include "linked_list.cpp"
//#include "track_queue.cpp"

bool running = true;
int runtime = 60 * 60 * 24;
int ticks = 0;

// Generate vehicle

int main(int args, char* argv[]) {
	using namespace std;
	using namespace structures;
	if(args == 2) {
		runtime = atoi(argv[1]);
	} else if (args > 2) {
		cout << "Por favor utilize " << argv[0] << " <tempo de simulação>\n";
		return 0;
	}

 	srand((unsigned int)time(NULL));

 	LinkedList<TrackQueue> tracks;
 	// Criar as 14 vias sendo que 6 surgem, 6 somem, e 2 ficam no meio
	// Declarar as filas
	// Declarar filas geradoras



	// Declarar os semaforos
	// Ver um jeito melhor de mandar os dados (txt)
	// Criar dois semaforos com direção que fica aberto e tempo (ticks)
	// Revisar esses dados para nova ordem
	int* northS1 = new int[3]{80, 10, 10};
	int* eastS1 = new int[3]{30, 30, 40};
	int* southS1 = new int[3]{10, 80, 10};
	int* westS1 = new int[3]{10, 10, 80};
	Semaphore sem1(northS1, eastS1, southS1, westS1);
	Semaphore sem2(new int[3]{30, 40, 30}, new int[3]{40, 30, 30}, new int[3]{30, 40, 30}, new int[3]{30, 30, 40});

	// Lista das pistas que se ligam no semaforo

	string names[] = {"NORTH", "EAST", "SOUTH", "WEST", "CLOSE"};

	while(running) {
		// Tick

		// Ticks do semaforo
		// Mudança de semaforo
		Direcao dirsem1 = sem1.direction();

		sem1.tick();
		sem2.tick();

		if(dirsem1 != sem1.direction()) {
			if(sem1.direction() == sem2.direction()) {
				cout << "Os semaforos estao sincronizados\n";
			}
			cout << "Estado do semaforo 1 mudou de " << names[dirsem1] << " para " << names[sem1.direction()] << '\n';
		}

		/*
		// Loop de todas as pistas para todos os carros andarem
		for (int i = 0; i < tracks.size(); i++) {
			TrackQueue queue = tracks.at(i);

			// Loop em todos os carros
			for(int y = 0; y < queue.vehicles(); y++) {
				Vehicle v = queue.at(y);
				v.andar(queue.speed()); // Só andar se tiver espaço livre
			}

			// Random gerador de carros (nao esquecer da checkagem se esta cheio)
			// Se a track for uma track geradora, gerar
		}

		// Loop das pistas apenas do semaforo
		/**
		Vehicle first = queue.last(); // Pega o ultimo

			// Chegada de carro no semáforo
			// Troca de pista (aleatorio) Setar direcao do veiculo
			if(first.isSemaforoDistance()) { // Se  for 0
				if()
				// Random para onde ele quer ir
				// Seta no carro qual a direçao
				if(vehicle)
				queue.dequeue(); // Sai da fila
			}
*/
		// cout << "Tick nº:" << ticks << '\n';
		if(++ticks > runtime)
			running = false;
	}

}