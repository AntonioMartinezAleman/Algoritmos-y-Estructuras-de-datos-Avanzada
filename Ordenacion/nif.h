#ifndef NIF_H
#define NIF_H

#include <iostream>
#include <cstdlib>

class nif {
private:
  long value_; // almacena el valor del DNI (8 cifras)
public:
  nif();                   // constructor aleatorio
  nif(long v);             // de long a nif
  operator long() const;   // de nif a long

  // Comparadores (necesarios para ordenación)
  bool operator==(const nif& other) const;
  bool operator!=(const nif& other) const;
  bool operator<(const nif& other) const;
  bool operator>(const nif& other) const;
  bool operator<=(const nif& other) const;
  bool operator>=(const nif& other) const;

  friend std::ostream& operator<<(std::ostream& os, const nif& x);
};

#endif
