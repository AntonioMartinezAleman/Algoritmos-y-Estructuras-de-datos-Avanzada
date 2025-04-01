#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "sequence.h"
#include "dynamicsequence.h"
#include "staticsequence.h"
#include "dispersionfunction.h"
#include "explorationfunction.h"
#include <vector>


// dispersion cerrada, Static
template <class Key, class Container = staticSequence<Key> >
class HashTable : public Sequence<Key> {
private:
  unsigned tableSize_; // tamaño total de la tabla
  unsigned blockSize_; // tamaño del bloque, cuantos elementos por casilla
  DispersionFunction<Key>& fd_; // funcionde dispersion
  ExplorationFunction<Key>& fe_; // funcion de exploracion
  std::vector<Container*> table_; // vector de punteros al container
public:
  HashTable(unsigned tableSize,
            DispersionFunction<Key>& fd,
            ExplorationFunction<Key>& fe,
            unsigned blockSize)
    : tableSize_(tableSize),
      blockSize_(blockSize),
      fd_(fd),
      fe_(fe) {
    table_.resize(tableSize_, nullptr);
    for (unsigned i = 0; i < tableSize_; i++) {
      table_[i] = new Container(blockSize_);
    }
  }
  ~HashTable() {
    for (unsigned i = 0; i < tableSize_; i++) {
      delete table_[i];
    }
  }
  bool search(const Key& k) const override {
    for (unsigned i = 0; i < tableSize_; i++) {
      unsigned idx = (fd_(k) + fe_(k, i)) % tableSize_;
      if (table_[idx]->search(k)) {
        return true;
      }
    }
    return false;
  }
  bool insert(const Key& k) override {
    for (unsigned i = 0; i < tableSize_; i++) {
      unsigned idx = (fd_(k) + fe_(k, i)) % tableSize_;
      if (table_[idx]->insert(k)) {
        return true;
      }
    }
    return false;
  }
};



//dispersion abierta, Dynamic
template <class Key>
class HashTable<Key, dynamicSequence<Key>> : public Sequence<Key> {
private:
  unsigned tableSize_;
  DispersionFunction<Key>& fd_;
  std::vector<dynamicSequence<Key>*> table_;

  // no hay ni blockSize ni funcion de exploración
  //Cada posición contiene un dynamicSequence<Key>*, que internamente es una std::list<Key>.
public:
  HashTable(unsigned tableSize, DispersionFunction<Key>& fd)
    : tableSize_(tableSize), fd_(fd) {
    table_.resize(tableSize_, nullptr);
    for (unsigned i = 0; i < tableSize_; i++) {
      table_[i] = new dynamicSequence<Key>();
    }
  }
  ~HashTable() {
    for (unsigned i = 0; i < tableSize_; i++) {
      delete table_[i];
    }
  }
  bool search(const Key& k) const override { //Simplemente busca en la lista (sin reintentar, porque colisiones se resuelven guardando todo en la misma lista).
    unsigned idx = fd_(k) % tableSize_;
    return table_[idx]->search(k);
  }
  bool insert(const Key& k) override {
    unsigned idx = fd_(k) % tableSize_;
    return table_[idx]->insert(k);
  }
};

#endif
