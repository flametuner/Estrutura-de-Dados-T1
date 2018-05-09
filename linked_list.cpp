#include "linked_list.h"

#include <stdexcept>

template <typename T>
void structures::LinkedList<T>::clear() {
  auto it = head;
  Node* copy;
  for (auto i = 1u; i <= size(); ++i) {
      copy = it;
      it = it->next();
      delete copy;
  }
  size_ = 0;
}

template <typename T>
void structures::LinkedList<T>::push_back(const T& data) {
  insert(data, size());
}

template <typename T>
void structures::LinkedList<T>::push_front(const T& data) {
  insert(data, 0);
}

template <typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
  // Implementação do insert
  if (index > size()) {
		throw std::out_of_range("Index fora do tamanho da lista");
	} else {
        if (index == 0) {
            head = new Node{data, head};
         } else {
            Node* it = head;
            for (auto i = 1u; i < index; ++i) {
                it = it->next();
            }
            Node* nn = new Node{data, it->next()};
            it->next(nn);
        }
        size_++;
    }
}

template <typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
  auto index = 0;
  // checkagem de valores;
  if (!empty()) {
    auto it = head;
		for(auto i = 1u; i <= size(); i++) {
			if (data < it->data()) {
					break;
			}
      index++;
      it = it->next();
		}
	}
  insert(data, index);
}

template <typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
  if (index >= size()) {
		throw std::out_of_range("A lista nao possui este objeto");
	} else {
    auto it = head;
    for (auto i = 1u; i <= index; ++i) {
        it = it->next();
    }
    return it->data();
  }
}

template <typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
  // Implementação do pop
  if (size() <= 0 || index >= size()) {
		throw std::out_of_range("Index fora do tamanho da lista");
	} else {
    auto it = head;
    if (index == 0) {
      head = it->next();
    } else {
      Node* last = nullptr;
      for (auto i = 1u; i <= index; ++i) {
          last = it;
          it = it->next();
      }
      last->next(it->next());
    }
    T object = it->data();
    delete it;
    size_--;
    return object;
	}
}

template <typename T>
T structures::LinkedList<T>::pop_back() {
  return pop(size() - 1);
}

template <typename T>
T structures::LinkedList<T>::pop_front() {
  return pop(0);
}

template <typename T>
void structures::LinkedList<T>::remove(const T& data) {
  int index = find(data);
  if (index < 0) {
    throw std::out_of_range("A lista nao possui este objeto");
  } else {
    pop(index);
  }
}

template <typename T>
bool structures::LinkedList<T>::empty() const {
  return size() <= 0;
}

template <typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
  return find(data) < size();
}

template <typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
  // Implementação do Find
  size_t index = -1;
  auto it = head;
  for (auto i = 1u; i <= size(); ++i) {
      if (it->data() == data) {
  			index = i - 1;
  			break;
  		}
      it = it->next();
  }
  if (index == -1)
    index = size();
	return index;
}

template <typename T>
std::size_t structures::LinkedList<T>::size() const {
  return size_;
}
