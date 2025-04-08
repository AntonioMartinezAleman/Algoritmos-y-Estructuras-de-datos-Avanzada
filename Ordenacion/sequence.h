#ifndef SEQUENCE_H
#define SEQUENCE_H

// Clase abstracta base para secuencias
template <class Key>
class Sequence {
public:
  virtual bool search(const Key& k) const = 0;
  virtual bool insert(const Key& k) = 0;

  // NUEVO: Operadores de acceso
  virtual Key operator[](const unsigned) const = 0;
  virtual Key& operator[](const unsigned) = 0;

  virtual ~Sequence() {}
};

#endif
