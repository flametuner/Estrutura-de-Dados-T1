#ifndef STRUCTURES_VEHICLE_H
#define STRUCTURES_VEHICLE_H

#include <stdlib.h>
#include <time.h>
#include "semaphore.h"

#define MAX_VEHICLE 3.0
namespace structures {

/// Veiculo

class Vehicle {
 public:
    Vehicle(float size, Direcao direction) : size_{size}, direction_{direction} {}
    	

    float size() const {
    	return size_;
    }
 private:
    float size_;
    Direcao direction_; // Direcao que ele quer ir
};

Vehicle generate_vehicle();

}  // namespace structures

#endif