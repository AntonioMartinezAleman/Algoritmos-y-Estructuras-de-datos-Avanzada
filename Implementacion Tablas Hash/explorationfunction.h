#ifndef EXPLORATIONFUNCTION_H
#define EXPLORATIONFUNCTION_H

#include "dispersionfunction.h" // si se requiere DoubleDispersion

template <class Key>
class ExplorationFunction {
public:
  virtual unsigned operator()(const Key& k, unsigned i) const = 0;
  virtual ~ExplorationFunction() {}
};

template <class Key> 
class LinearExploration : public ExplorationFunction<Key> {
public:
  unsigned operator()(const Key&, unsigned i) const override {
    return i;
  }
}; //desplazamiento sumado a la posicion base

template <class Key>
class QuadraticExploration : public ExplorationFunction<Key> {
public:
  unsigned operator()(const Key&, unsigned i) const override {
    return i * i; //desplazamiento es i^2
  }
};

template <class Key>
class DoubleDispersion : public ExplorationFunction<Key> {
private:
  DispersionFunction<Key>& fd_;
public:
  DoubleDispersion(DispersionFunction<Key>& fd) : fd_(fd) {}
  unsigned operator()(const Key& k, unsigned i) const override {
    unsigned aux = fd_(k);
    return aux * i;
  }
};

template <class Key>
class ReDispersion : public ExplorationFunction<Key> {
public:
  unsigned operator()(const Key& k, unsigned i) const override {
    long val = (long)k;
    std::srand((unsigned)val);
    unsigned r = 0;
    for (unsigned j = 0; j <= i; j++) {
      r = std::rand();
    }
    return r;
  }
}; // cada intento de busqueda es un numero aleatorio a partir de val

#endif
