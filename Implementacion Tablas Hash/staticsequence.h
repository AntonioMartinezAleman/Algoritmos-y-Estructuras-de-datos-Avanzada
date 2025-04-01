#ifndef STATICSEQUENCE_H
#define STATICSEQUENCE_H

#include "sequence.h"
#include <vector>
#include <algorithm>

template <class Key>
class staticSequence : public Sequence<Key> {
private:
  unsigned blockSize_; //tamaño maximo de la secuencia
  std::vector<Key> data_; // contenedor donde ponemos los elementos
public:
  staticSequence(unsigned blockSize) : blockSize_(blockSize) { // reserva memoria dependiendo del blockSize
    data_.reserve(blockSize_);
  }
  bool isFull() const {
    return (data_.size() >= blockSize_);
  }
  bool search(const Key& k) const override { //busca para ver si k esta en el vector
    auto it = std::find(data_.begin(), data_.end(), k);
    return (it != data_.end());
  }
  bool insert(const Key& k) override { // si no esta lleno, inserta
    if (isFull()) {
      return false;
    }
    data_.push_back(k);
    return true;
  }
};

#endif
