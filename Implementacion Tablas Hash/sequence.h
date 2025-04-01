#ifndef SEQUENCE_H
#define SEQUENCE_H

//clase que se encarga de almacenar los elementos que caen en cada posicion de la tabla hash

template <class Key>
class Sequence {
public:
  virtual bool search(const Key& k) const = 0; // busca si hay o no un elemento en la tabla
  virtual bool insert(const Key& k) = 0; // si podemos o no insertar un nuevo elemento
  virtual ~Sequence() {}
};

#endif
