#include "vehicle.h"

 structures::Vehicle* structures::generate_vehicle(float distance, structures::Direcao direction){
    Vehicle* v = new Vehicle(4 + ((float)rand()/(float)(RAND_MAX))*MAX_VEHICLE, direction, distance);
    return v;
}

void structures::Vehicle::move(float distance) {
	distance_ -= distance;
}

void structures::Vehicle::changeTrack(float distance, structures::Direcao direction) {
  distance_ = distance;
  direction_ = direction;
}
