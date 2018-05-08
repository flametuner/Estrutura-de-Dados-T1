#ifndef STRUCTURES_SEMAPHORE_H
#define STRUCTURES_SEMAPHORE_H

#define OPEN_TIME 40

namespace structures {

enum Direcao
{
        NORTH,
        EAST,
        SOUTH,
        WEST,
        CLOSE
};

class Semaphore {

 public:
 	Semaphore(int north[3], int south[3], int east[3], int west[3]) {
 		probability_ = new int*[4];
 		probability_[Direcao::NORTH] = north;
 		probability_[Direcao::SOUTH] = south;
 		probability_[Direcao::EAST] = east;
 		probability_[Direcao::WEST] = west;
 		currentDirection = Direcao::CLOSE;
 		ticksOpen = 0;
 	}

 	~Semaphore() {
 		delete[] probability_;
 	}

 	void tick() {
	 	if(ticksOpen-- < -5)
	 		updateDirection();
 	}


 	Direcao direction() {
 		if(ticksOpen <= 0)
 			return Direcao::CLOSE;
 		return currentDirection;
 	}

 	int* probability(Direcao dir) {
 		return probability_[dir];
 	}


 private:
 	int ticksOpen;
 	Direcao currentDirection;
 	int** probability_;

 	void updateDirection() {
 		int i = currentDirection + 1;
 		currentDirection = Direcao(i % 4);
	 	ticksOpen = OPEN_TIME;
 	}

};

}
#endif