#ifndef NIF_H
#define NIF_H

#include <iostream>
#include <cstdlib>


class nif {
private:
  long value_; //almacena valor del dni (8 cifras)
public:
  nif(); //genera valor aleatorio
  nif(long v); // de long a nif
  operator long() const; //pasa de nif a long

  bool operator==(const nif& other) const;
  bool operator!=(const nif& other) const;
  bool operator<(const nif& other) const;
  
  friend std::ostream& operator<<(std::ostream& os, const nif& x);
};

#endif
