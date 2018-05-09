#include "semaphore.h"
#include "track_queue.h"

using namespace structures;

Semaphore::Semaphore(int north[3], int south[3], int east[3], int west[3], TrackQueue** entradas, TrackQueue** saidas) {
  probability_ = new int*[4];
  entradas_ = entradas;
  saidas_ = saidas;
  probability_[Direcao::NORTH] = north;
  probability_[Direcao::SOUTH] = south;
  probability_[Direcao::EAST] = east;
  probability_[Direcao::WEST] = west;
  currentDirection = Direcao::WEST;
  ticksOpen = 0;
}

Semaphore::~Semaphore() {
  delete[] probability_;
}

void Semaphore::tick() {
  if(ticksOpen-- < -5)
    updateDirection();
}

Direcao Semaphore::direction() {
  if(ticksOpen <= 0)
    return Direcao::CLOSE;
  return currentDirection;
}

int* Semaphore::probability(Direcao dir) {
  if(dir >= 4)
    return nullptr;
  return probability_[dir];
}

void Semaphore::updateDirection() {
  int i = currentDirection + 1;
  currentDirection = Direcao(i % 4);
  ticksOpen = OPEN_TIME;
}

TrackQueue* Semaphore::getOpenTrack() {
  return entradas_[currentDirection];
}

TrackQueue* Semaphore::getExit(Direcao dir) {
  return saidas_[dir];
}
