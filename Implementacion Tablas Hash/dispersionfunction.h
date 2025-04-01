#ifndef DISPERSIONFUNCTION_H
#define DISPERSIONFUNCTION_H

#include <cstdlib>

template <class Key>
class DispersionFunction { //Dado un objeto k de tipo Key, devuélveme un unsigned que será la posición en la tabla hash
public:
  virtual unsigned operator()(const Key& k) const = 0;
  virtual ~DispersionFunction() {}
};

template <class Key>
class ModuloDispersion : public DispersionFunction<Key> {
private:
  unsigned tableSize_; //cuantas posiciones hay en la tabla
public:
  ModuloDispersion(unsigned tableSize) : tableSize_(tableSize) {}
  unsigned operator()(const Key& k) const override {
    long val = (long)k;
    return (unsigned)(val % tableSize_); // devuelve posicion entre 0 y tablesize -1
  }
};

template <class Key> 
class SumDispersion : public DispersionFunction<Key> {
private:
  unsigned tableSize_;
public:
  SumDispersion(unsigned tableSize) : tableSize_(tableSize) {}
  unsigned operator()(const Key& k) const override {
    long val = (long)k;
    if (val < 0) val = -val;
    unsigned sum = 0;
    while (val > 0) {
      sum += (val % 10);
      val /= 10;
    }
    return sum % tableSize_; //dispersion por suma de digitos
  }
};

template <class Key>
class RandomDispersion : public DispersionFunction<Key> {
private:
  unsigned tableSize_;
public:
  RandomDispersion(unsigned tableSize) : tableSize_(tableSize) {}
  unsigned operator()(const Key& k) const override {
    long val = (long)k;
    std::srand((unsigned)val); //genera valor semilla
    return std::rand() % tableSize_; // modulo de semilla % tableSize
  }
};

#endif
