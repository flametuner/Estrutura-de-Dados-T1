#ifndef STRUCTURES_VEHICLE_H
#define STRUCTURES_VEHICLE_H

#include <stdlib.h>
#include <time.h>
#include "direcao.h"

#define MAX_VEHICLE 3.0
namespace structures {

/// Veiculo

class Vehicle {
 public:
    Vehicle(float size, structures::Direcao direction, float distance)
      :   size_{size},
          direction_{direction},
          distance_{distance} {}
    ~Vehicle();
    void move(float distance);

    void changeTrack(float distance, structures::Direcao direction);

    float size() const {
    	return size_;
    }

    Direcao direction() {
      return direction_;
    }

    float distance() const {
      return distance_;
    }
 private:
    float size_;
    float distance_;
    Direcao direction_; // Direcao que ele quer ir
};

Vehicle* generate_vehicle(float distance, structures::Direcao direction);

}  // namespace structures

#endif
