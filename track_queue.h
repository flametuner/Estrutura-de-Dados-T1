#ifndef STRUCTURES_TRACK_QUEUE_H
#define STRUCTURES_TRACK_QUEUE_H

#include "linked_queue.h"
#include "vehicle.h"
#include "direcao.h"
#include <cstdint>

namespace structures {

/// Fila encadeada
class TrackQueue {
 public:
    TrackQueue(float speed, int lenght) :  TrackQueue(speed, lenght, Sem::EXIT, Direcao::CLOSE) {}
    TrackQueue(float speed, int lenght, Direcao dir) :  TrackQueue(speed, lenght, Sem::EXIT, dir) {}
    TrackQueue(float speed, int lenght, Sem destino, Direcao dir) :  TrackQueue(speed, lenght, destino, dir, 0, 0) {}
    TrackQueue(float speed, int lenght, Sem destino, Direcao dir, int generationMin, int generationMax);
    ~TrackQueue();
    /// Adiciona na fila
    void enqueue(Vehicle* data);
    /// Tira da fila
    structures::Vehicle* dequeue();
    /// Fila vazia
    bool empty() const;
    /// Pode gerar
    bool canGenerateCar();
    /// Localiza veiculos no lugar
    Vehicle* at(std::size_t index);
    /// Fila cheia
    bool hasSpace(float size) const;
    /// Size of vehicles
    std::size_t vehicles();
    /// Carros que entraram nela, pra estatisticas
    int carrosPassados();
    /// Velocidade
    float speed() const;
    /// Tamanho da fila
    float queueSize() const;
    /// Tamanho da pista
    float lenght() const;

    Vehicle* front();

    Sem destino();

    Direcao semDirection();

    void addQueue(float distance);
 private:
    structures::LinkedQueue<Vehicle*>* vehicles_;
    float speed_; // m/s
    float queueSize_; // tamanho maximo da via
    float lenght_; // tamanho atual da fila
    int estatisticas_ = 0;
    Direcao semDirection_;
    Sem destino_;
    int generationMax_, generationMin_, nextGeneration; // detalhes de geração
};

}  // namespace structures

#endif
