#include "linked_queue.h"
#include "linked_list.cpp"
#include <stdexcept>

template <typename T>
void structures::LinkedQueue<T>::clear() {
	structures::LinkedList<T>::clear();
}

template <typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
	structures::LinkedList<T>::push_front(data);
	if(size() == 1)
		tail = structures::LinkedList<T>::end();
}

template <typename T>
T structures::LinkedQueue<T>::dequeue() {
	T t = structures::LinkedList<T>::pop_back();
	tail = structures::LinkedList<T>::end();
	return t;
}

template <typename T>
T& structures::LinkedQueue<T>::front() const {
	if(size() <= 0)
		throw std::out_of_range("A fila esta vazia");
	return tail->data();
}

template <typename T>
T& structures::LinkedQueue<T>::back() const {
	if(size() <= 0)
		throw std::out_of_range("A fila esta vazia");
	return structures::LinkedList<T>::head->data();
}

template <typename T>
bool structures::LinkedQueue<T>::empty() const {
	return structures::LinkedList<T>::empty();
}

template <typename T>
std::size_t structures::LinkedQueue<T>::size() const {
	return structures::LinkedList<T>::size();
}

template <typename T>
T& structures::LinkedQueue<T>::at(std::size_t index) {
	return structures::LinkedList<T>::at(index);
}
