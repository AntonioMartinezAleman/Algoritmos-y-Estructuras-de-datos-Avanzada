#ifndef DYNAMICSEQUENCE_H
#define DYNAMICSEQUENCE_H

#include "sequence.h"
#include <list>
#include <algorithm>

template <class Key>
class dynamicSequence : public Sequence<Key> {
private:
  std::list<Key> data_; //almacena los datos
public:
  dynamicSequence() {}
  bool search(const Key& k) const override { // busca si hay un elemento o no en la lista
    auto it = std::find(data_.begin(), data_.end(), k);
    return (it != data_.end());
  }
  bool insert(const Key& k) override { //añade el elemento y devuelve y true porque partimos de memoria infinita
    data_.push_back(k);
    return true;
  }
};

#endif
