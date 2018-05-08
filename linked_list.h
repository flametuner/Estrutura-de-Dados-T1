#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

/// Classe de Lista encadeada
template<typename T>
class LinkedList {
 public:
    LinkedList();
    ~LinkedList();
    /// Limpa a lista
    void clear();
    /// Insere no fim
    void push_back(const T& data);
    /// Insere no inicio
    void push_front(const T& data);
    /// Insere na posição
    void insert(const T& data, std::size_t index);
    /// Insere em ordem
    void insert_sorted(const T& data);
    /// Acessa um elemento na posição index
    T& at(std::size_t index);
    /// Retira da posição
    T pop(std::size_t index);
    /// Retira do fim
    T pop_back();
    /// Retira do inicio
    T pop_front();
    /// Remove um objeto tipo T
    void remove(const T& data);
    /// Retorna se a lista esta vazia
    bool empty() const;
    /// Checka se um objeto cotem
    bool contains(const T& data) const;
    /// Retorna a posição de um dado
    std::size_t find(const T& data) const;
    /// Retorna o tamanho da lista
    std::size_t size() const;

 protected:
    class Node {	 	  	 	      	      	      	      	 	   	       	 	
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {	 	  	 	      	      	      	      	 	   	       	 	
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif