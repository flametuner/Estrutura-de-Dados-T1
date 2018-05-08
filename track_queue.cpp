#include "track_queue.h"

structures::TrackQueue::TrackQueue() {
	vehicles = new LinkedQueue<Vehicle>;
}

structures::TrackQueue::~TrackQueue() {
	delete vehicles;
}

void structures::TrackQueue::enqueue(const structures::Vehicle& data) {
	vehicles->enqueue(data);
	lenght += data.size();
}

structures::Vehicle structures::TrackQueue::dequeue(){
	return vehicles->dequeue();
}

bool structures::TrackQueue::empty() const{
	return vehicles->empty();
}

bool structures::TrackQueue::hasSpace(float size) const{
	return (lenght + size) >= lenghtMax;
}

float structures::TrackQueue::size() const{
	return lenght;
}
