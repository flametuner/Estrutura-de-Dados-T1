#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>
#include <stdexcept>
#include "linked_list.h"

namespace structures {

/// Fila encadeada
template<typename T>
class LinkedQueue : private LinkedList<T> {
 public:
    /// Limpa a fila
    void clear();
    /// Adiciona na fila
    void enqueue(const T& data);
    /// Tira da fila
    T dequeue();
    /// Primeiro da fila
    T& front() const;
    /// Ultimo da fila
    T& back() const;
    // Diz qual o valor que esta numa determinada posição
    T& at(std::size_t index);
    /// Fila vazia
    bool empty() const;
    /// Tamanho da fila
    std::size_t size() const;
 private:
    typename structures::LinkedList<T>::Node* tail{nullptr};
};

}  // namespace structures

#endif