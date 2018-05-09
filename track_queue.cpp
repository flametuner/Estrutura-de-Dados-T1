#include "track_queue.h"
#include "linked_queue.cpp"

structures::TrackQueue::TrackQueue(float speed, int lenght, Sem destino, Direcao dir, int generationMin, int generationMax) {
	vehicles_ = new structures::LinkedQueue<structures::Vehicle*>();
	speed_ = speed;
	lenght_ = lenght;
	destino_ = destino;
	semDirection_ = dir;
	generationMax_ = generationMax;
	generationMin_ = generationMin;
	nextGeneration = 0;
	queueSize_ = 0;
}

structures::TrackQueue::~TrackQueue() {
	delete vehicles_;
}

structures::Vehicle* structures::TrackQueue::at(std::size_t index) {
	return vehicles_->at(index);
}

structures::Vehicle* structures::TrackQueue::front() {
	return vehicles_->front();
}

void structures::TrackQueue::enqueue(structures::Vehicle* data) {
	vehicles_->enqueue(data);
}

structures::Vehicle* structures::TrackQueue::dequeue(){
	queueSize_ = 0;
	return vehicles_->dequeue();
}

bool structures::TrackQueue::canGenerateCar() {
	if(generationMax_ <= 0)
		return false;
	if(nextGeneration-- <= 0) {
		nextGeneration = generationMin_ + (rand() % (generationMax_ - generationMin_));
		return true;
	}
	return false;
}

bool structures::TrackQueue::empty() const {
	return vehicles_->empty();
}

bool structures::TrackQueue::hasSpace(float size) const{
	return (queueSize_ + size) <= lenght_;
}

float structures::TrackQueue::queueSize() const{
	return queueSize_;
}

float structures::TrackQueue::speed() const{
	return speed_;
}

std::size_t structures::TrackQueue::vehicles() {
	return vehicles_->size();
}

structures::Sem structures::TrackQueue::destino() {
	return destino_;
}

structures::Direcao structures::TrackQueue::semDirection() {
	return semDirection_;
}

void structures::TrackQueue::addQueue(float distance) {
	queueSize_ += distance;
}

float structures::TrackQueue::lenght() const {
	return lenght_;
}
