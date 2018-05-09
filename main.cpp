#include <iostream>
#include <stdlib.h>
#include "semaphore.h"
#include "linked_list.h"
#include "linked_queue.h"
#include "track_queue.cpp"
#include "semaphore.cpp"
#include "direcao.h"
//#include "track_queue.cpp"

#include "vehicle.cpp"

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

	// Criar as 14 vias sendo que 6 surgem, 6 somem, e 2 ficam no meio
	// Declarar as filas
	// Declarar filas geradoras

 	LinkedList<TrackQueue*>* tracks = new LinkedList<TrackQueue*>();

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


	//TrackQueue t = tracks->at(0);
	//cout << "Comecando simulação\n";

	// Declarar os semaforos
	// Ver um jeito melhor de mandar os dados (txt)
	// Criar dois semaforos com direção que fica aberto e tempo (ticks)
	// Revisar esses dados para nova ordem
	int* northS1 = new int[3]{80, 10, 10};
	int* eastS1 = new int[3]{30, 30, 40};
	int* southS1 = new int[3]{10, 80, 10};
	int* westS1 = new int[3]{10, 10, 80};

	// Lista das pistas que se ligam no semaforo

	TrackQueue** entradas_sem1 = new TrackQueue*[4]{N1Sul, C1Oeste, S1Norte, O1Leste};
	TrackQueue** saidas_sem1 = new TrackQueue*[4]{N1Norte, C1Leste, S1Sul, O1Oeste};

	TrackQueue** entradas_sem2 = new TrackQueue*[4]{N2Sul, L1Oeste, S2Norte, C1Leste};
	TrackQueue** saidas_sem2 = new TrackQueue*[4]{N2Norte, L1Leste, S2Sul, C1Oeste};

	Semaphore* sem1 = new Semaphore(northS1, eastS1, southS1, westS1, entradas_sem1, saidas_sem1);
	Semaphore* sem2 = new Semaphore(new int[3]{30, 40, 30}, new int[3]{40, 30, 30}, new int[3]{30, 40, 30}, new int[3]{30, 30, 40}, entradas_sem2, saidas_sem2);

	LinkedList<Semaphore*> semList;
	semList.push_back(sem1);
	semList.push_back(sem2);

	string names[] = {"NORTH", "EAST", "SOUTH", "WEST", "CLOSE"};

	while(running) {
		// Tick
		Direcao dirsem1 = sem1->direction();
		// Ticks do semaforo
		// Mudança de semaforo
		sem1->tick();
		sem2->tick();

		// Loop de todas as pistas para todos os carros andarem

		for (int i = 0; i < tracks->size(); i++) {

			bool shouldDequeue = false;
			TrackQueue* queue = tracks->at(i);
			// Loop em todos os carros
			//cout << "Track> " << i << '\n';
			for(int y = 0; y < queue->vehicles(); y++) {
				Vehicle* v = queue->at(y);
				// Colocar a checkagem se pode andar ou não
				if(v == queue->front() && v->distance() <= queue->queueSize()) { // Primeiro da fila
					if(queue->destino() == Sem::EXIT) { // Se for fila sumidoura, deve sair
						shouldDequeue = true;
					}
					continue;
				}
				float distance = queue->speed() / 3.6;
				//cout << distance << '\n';
				//cout << "queuesize :" <<  queue->queueSize() << '\n';
				if((v->distance() - distance) < queue->queueSize()){
					if (v->distance() - distance - queue->queueSize() < 0 && v->distance() >= queue->queueSize())
							distance = v->distance() - queue->queueSize();
					else
						distance = 0; // Só andar se tiver espaço livre
				}
				v->move(distance);

				// Há uma fila e precisa aumentar

				if(v->distance() <= queue->queueSize()){
					queue->addQueue(v->size());
				}
			}
			if(shouldDequeue) {
				queue->dequeue();
				cout << "Saiu pelo sumidouro nº " << i << '\n';
			}
			// Random gerador de carros (nao esquecer da checkagem se esta cheio)
			// Se a track for uma track geradora, gerar
			if(queue->canGenerateCar()) {
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
				Vehicle* v = generate_vehicle(queue->lenght(), dir);

				if(queue->hasSpace(v->size())) {
					queue->enqueue(v);
					cout << "Carro gerado e adicionado na pista nº " << i << '\n';
				}
			}
			// cout << "veiculos na pista: " << queue->vehicles() << '\n';
		}

		for(int i = 0; i < semList.size(); i++) {
			Semaphore* sem = semList.at(i);
			if(sem->direction() != Direcao::CLOSE) {
				TrackQueue* openTrack = sem->getOpenTrack();
				if(openTrack->vehicles() <= 0)
					continue;
				//cout << "Veiculos na pista: [" << i << "][" << names[sem->direction()] << "] " << openTrack->vehicles() << '\n';
				Vehicle* v = openTrack->front();
				//cout << "Distancia do primeiro veiculo: " << v->distance() << '\n';
				//cout << "Tamanho da fila: " << openTrack->queueSize() << '\n';
				//cout << "Distancia do veiculo: " << v->distance() << '\n';
				TrackQueue* destiny = sem->getExit(v->direction());
				//cout << "dis: " << v->distance() << '\n';
				if(v->distance() <= 0 && destiny->hasSpace(v->size())) {
					//cout << "Mudança de pist\n";
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
		//cout << "Tick nº:" << ticks << '\n';
		if(++ticks > runtime)
			running = false;
	}
	delete tracks;
	cout << "Fim de simulação\n";

}
