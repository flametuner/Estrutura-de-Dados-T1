// "Copyright 2018 Gustavo Inácio e Juliano Santos"

#include <iostream>
#include <stdlib.h>

#include "semaphore.h"
#include "linked_list.h"
#include "linked_queue.h"
#include "direcao.h"

#include "track_queue.cpp"
#include "semaphore.cpp"
#include "vehicle.cpp"

bool running = true;
int runtime = 60 * 60 * 24;
int ticks = 0;

// Estatisticas
int carrosGerados = 0, carrosSumidos = 0, trocasDePista = 0, carrosNaoGerados = 0, vehiclesNasPistas = 0;

// TODO Ver para utilizar os dados do .txt

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

	// Criar as 14 vias sendo que 6 surgem, 6 somem, e 2 ficam no meio
	// Declarar as filas
	// Declarar filas geradoras

 	LinkedList<TrackQueue*>* tracks = new LinkedList<TrackQueue*>(); // delete no final do main

	// Tracks geradoras
	TrackQueue* N1Sul = new TrackQueue(60, 500, Sem::SEMAPHORE_1, Direcao::NORTH, 15, 25); // Semaforo 1
	TrackQueue* S1Norte = new TrackQueue(60, 500, Sem::SEMAPHORE_1, Direcao::SOUTH, 23, 37); // Semaforo 1
	TrackQueue* O1Leste = new TrackQueue(80, 2000, Sem::SEMAPHORE_1, Direcao::WEST, 8, 12); // Semaforo 1
	TrackQueue* N2Sul = new TrackQueue(40, 500, Sem::SEMAPHORE_2, Direcao::NORTH, 15, 25); // Semaforo 2
	TrackQueue* S2Norte = new TrackQueue(40, 500, Sem::SEMAPHORE_2, Direcao::SOUTH, 45, 75); // Semaforo 2
	TrackQueue* L1Oeste = new TrackQueue(30, 400, Sem::SEMAPHORE_2, Direcao::EAST, 8, 12); // Semaforo 2

	// Tracks sumidouras
	TrackQueue* S1Sul = new TrackQueue(60, 500); // Semaforo 1
	TrackQueue* N1Norte = new TrackQueue(60, 500); // Semaforo 1
	TrackQueue* O1Oeste = new TrackQueue(80, 2000); // Semaforo 1

	TrackQueue* S2Sul = new TrackQueue(40, 500); // Semaforo 2
	TrackQueue* N2Norte = new TrackQueue(40, 500); // Semaforo 2
	TrackQueue* L1Leste = new TrackQueue(30, 400); // Semaforo 2

	// Tracks centrais
	TrackQueue* C1Oeste = new TrackQueue(60, 300, Sem::SEMAPHORE_1, Direcao::EAST); // Semaforo 1
	TrackQueue* C1Leste = new TrackQueue(60, 300, Sem::SEMAPHORE_2, Direcao::WEST); // Semaforo 2

	tracks->push_back(N1Sul);
	tracks->push_back(S1Norte);
	tracks->push_back(O1Leste);
	tracks->push_back(N2Sul);
	tracks->push_back(S2Norte);
	tracks->push_back(L1Oeste);
	tracks->push_back(S1Sul);
	tracks->push_back(N1Norte);
	tracks->push_back(O1Oeste);
	tracks->push_back(S2Sul);
	tracks->push_back(N2Norte);
	tracks->push_back(L1Leste);
	tracks->push_back(C1Oeste);
	tracks->push_back(C1Leste);
	// delete em todas no final com loop

	// delete dentro do semaforo
	int* northS1 = new int[3]{80, 10, 10};
	int* eastS1 = new int[3]{30, 30, 40};
	int* southS1 = new int[3]{10, 80, 10};
	int* westS1 = new int[3]{10, 80, 10};

	// Lista das pistas que se ligam no semaforo

	//Array de Ponteiros para Semaforos
	TrackQueue** entradas_sem1 = new TrackQueue*[4]{N1Sul, C1Oeste, S1Norte, O1Leste}; 	// delete dentro do semaforo
	TrackQueue** saidas_sem1 = new TrackQueue*[4]{N1Norte, C1Leste, S1Sul, O1Oeste}; 	// delete dentro do semaforo

	TrackQueue** entradas_sem2 = new TrackQueue*[4]{N2Sul, L1Oeste, S2Norte, C1Leste};	// delete dentro do semaforo
	TrackQueue** saidas_sem2 = new TrackQueue*[4]{N2Norte, L1Leste, S2Sul, C1Oeste};	// delete dentro do semaforo

	// Declarar os semaforos
	Semaphore* sem1 = new Semaphore(northS1, eastS1, southS1, westS1, entradas_sem1, saidas_sem1);
	Semaphore* sem2 = new Semaphore(new int[3]{40, 30, 30}, new int[3]{40, 30, 30}, new int[3]{30, 40, 30}, new int[3]{30, 40, 30}, entradas_sem2, saidas_sem2);

	LinkedList<Semaphore*> semList;
	semList.push_back(sem1);
	semList.push_back(sem2);
	// Delete no final do main em Loop
	cout << "Inicio de simulação\n";

	string names[] = {"NORTH", "EAST", "SOUTH", "WEST", "CLOSE"};
	string names2[] = {"SEMAPHORE_1", "SEMAPHORE_2", "EXIT"};

	while(running) {
		// Tick
		Direcao dirsem1 = sem1->direction();
		// Ticks do semaforo
		sem1->tick();
		sem2->tick();

		// Loop de todas as pistas para todos os carros andarem

		for (int i = 0; i < tracks->size(); i++) {

			bool shouldDequeue = false;
			TrackQueue* queue = tracks->at(i);
			// Loop em todos os carros

			for(int y = 0; y < queue->vehicles(); y++) {
				Vehicle* v = queue->at(y);
				// Checkagem se pode andar ou não

				if(v->distance() == 0 && v->distance() <= queue->queueSize()) { // Primeiro da fila
					if(queue->destino() == Sem::EXIT) { // Se for fila sumidoura, deve sair
						delete queue->dequeue(); // Delete de carro
						carrosSumidos++;
						vehiclesNasPistas--;
						y--;
					}
					continue;
				}
				float distance = queue->speed() / 3.6;

				if((v->distance() - distance) <= queue->queueSize()){
					if (v->distance() > queue->queueSize())
							distance = v->distance() - queue->queueSize();
					else
						distance = 0; // Só andar se tiver espaço livre
				}
				v->move(distance);

				// Há uma fila e precisa aumentar

				if(v->distance() <= queue->queueSize() && distance == 0){
					queue->addQueue(v->size());
				}
			}


			// Se a track for uma track geradora, gerar
			if(queue->canGenerateCar() && ticks < runtime) {
				int* probability{nullptr};
				if(queue->destino() == Sem::SEMAPHORE_1) {
					probability = sem1->probability(queue->semDirection());
				} else {
					probability = sem2->probability(queue->semDirection());
				}
				int chance = rand() % 100;

				int choice = 0;
				int pass = 0;
				for(int j = 0; j < 4; j++) {
					if(j == queue->semDirection()) {
						pass++;
						continue;
					}
					if(chance < probability[j - pass]) {
						choice = j;
						break;
					} else {
						chance -= probability[j - pass];
					}
				}

				Direcao dir = Direcao(choice);
				Vehicle* v = generate_vehicle(queue->lenght(), dir); // Geração de carros

				if(queue->hasSpace(v->size())) {
					queue->enqueue(v);
					vehiclesNasPistas++;
					carrosGerados++;
				} else {
					carrosNaoGerados++;
				}
			}
		}

		for(int i = 0; i < semList.size(); i++) {
			Semaphore* sem = semList.at(i);
			if(sem->direction() != Direcao::CLOSE) {
				TrackQueue* openTrack = sem->getOpenTrack();
				if(openTrack->vehicles() <= 0)
					continue;
				Vehicle* v = openTrack->front();

				TrackQueue* destiny = sem->getExit(v->direction());
				if(v->distance() <= 0 && destiny->hasSpace(v->size())) {
					trocasDePista++;
					// Geração de novo destino
					int* probability{nullptr};
					if(openTrack->destino() == Sem::SEMAPHORE_1) {
						probability = sem1->probability(openTrack->semDirection());
					} else {
						probability = sem2->probability(openTrack->semDirection());
					}
					int chance = rand() % 100;

					int choice = 0;
					int pass = 0;
					for(int j = 0; j < 4; j++) {
						if(j == openTrack->semDirection()) {
							pass++;
							continue;
						}
						if(chance < probability[j - pass]) {
							choice = j;
							break;
						} else {
							chance -= probability[j - pass];
						}
					}

					Direcao dir = Direcao(choice);
					v->changeTrack(destiny->lenght(), dir);
					destiny->enqueue(openTrack->dequeue());
				}
			}
		}
		if(++ticks > runtime)
			running = false;
	}

	for(int i = 0; i < semList.size(); i++) {
		delete semList.at(i); // Delete semaforos
	}
	cout << "Fim de simulação\n";
	cout << "Ticks rodados: " << (ticks - 1) << '\n';
	cout << "Carros gerados: " << carrosGerados << '\n';
	cout << "Carros nao gerados: " << carrosNaoGerados << '\n';
	cout << "Veiculos na pista no momento: " << vehiclesNasPistas << '\n';
	cout << "Carros sumidos: " << carrosSumidos << '\n';
	cout << "Trocas de pista: " << trocasDePista << '\n';
	cout << "\nPista(n) [Direção, Destino] : Carros que passaram\n\n";
	for(int i = 0; i < tracks->size(); i++) {
		TrackQueue* queue = tracks->at(i);
		cout << "Pista(" << i << ") [" << names[queue->semDirection()] << ", " << names2[queue->destino()]<< "]" << ": " << queue->carrosPassados() << '\n';
		delete queue; // Delete tracks
	}

	delete tracks; // delete array de pista

}
