#ifndef STRUCTURES_SEMAPHORE_H
#define STRUCTURES_SEMAPHORE_H

#define OPEN_TIME 45
#include "track_queue.h"
#include "direcao.h"

namespace structures {

class Semaphore {

 public:
 	Semaphore(int north[3], int south[3], int east[3], int west[3], TrackQueue** entradas, TrackQueue** saidas);
 	~Semaphore();
 	void tick();
 	Direcao direction();
 	int* probability(Direcao dir);
  TrackQueue* getOpenTrack();
  TrackQueue* getExit(Direcao dir);
 private:
 	int ticksOpen;
 	Direcao currentDirection;
 	int** probability_;
  TrackQueue** entradas_{nullptr};
  TrackQueue** saidas_{nullptr};
 	void updateDirection();
};

}
#endif
