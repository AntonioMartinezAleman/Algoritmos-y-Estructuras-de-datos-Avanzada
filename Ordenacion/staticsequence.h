#ifndef STATICSEQUENCE_H
#define STATICSEQUENCE_H

#include "sequence.h"
#include <vector>
#include <algorithm>

template <class Key>
class staticSequence : public Sequence<Key> {
private:
  unsigned blockSize_;            // Tamaño máximo de la secuencia
  std::vector<Key> data_;         // Contenedor de elementos

public:
  staticSequence(unsigned blockSize) : blockSize_(blockSize) {
    data_.reserve(blockSize_);
  }

  bool isFull() const {
    return (data_.size() >= blockSize_);
  }

  bool search(const Key& k) const override {
    auto it = std::find(data_.begin(), data_.end(), k);
    return (it != data_.end());
  }

  bool insert(const Key& k) override {
    if (isFull()) return false;
    data_.push_back(k);
    return true;
  }

  // Operadores [] para acceso/modificación
  Key operator[](const unsigned index) const override {
    return data_.at(index);
  }

  Key& operator[](const unsigned index) override {
    return data_.at(index);
  }

  // NUEVO: obtener tamaño actual (útil en Sort)
  unsigned size() const {
    return data_.size();
  }
};

#endif
