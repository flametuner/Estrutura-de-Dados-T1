 #include "vehicle.h"
 
 structures::Vehicle structures::generate_vehicle(){

    structures::Vehicle v(4 + ((float)rand()/(float)(RAND_MAX))*MAX_VEHICLE, Direcao(rand()%4));
    
    return v;
}