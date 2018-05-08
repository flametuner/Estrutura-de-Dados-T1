#ifndef STRUCTURES_TRACK_QUEUE_H
#define STRUCTURES_TRACK_QUEUE_H

#include <cstdint>
#include <stdexcept>
#include "linked_queue.h"
#include "vehicle.h"

namespace structures {

/// Fila encadeada
class TrackQueue {
 public:
    TrackQueue();
    ~TrackQueue();
    /// Adiciona na fila
    void enqueue(const Vehicle& data);
    /// Tira da fila
    structures::Vehicle dequeue();
    /// Fila vazia
    bool empty() const;
    /// Fila cheia
    bool hasSpace(float size) const; 
    /// Tamanho da fila
    float size() const;
 private:
    LinkedQueue<Vehicle>* vehicles;
    float speed; // m/s
    int lenghtMax; // tamanho maximo da via
    float lenght; // tamanho atual da fila
    int generationMax, generationMin; // detalhes de geração
};

}  // namespace structures

#endif