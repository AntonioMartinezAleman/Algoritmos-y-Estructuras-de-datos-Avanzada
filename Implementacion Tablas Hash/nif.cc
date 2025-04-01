#include "nif.h"
#include <cstdlib>

nif::nif() {
  value_ = std::rand() % 100000000; // valor aleatorio de 8 digitos
}

nif::nif(long v) { 
  if (v < 0) v = -v; //lo convertimos a positivo
  value_ = v % 100000000; //nos quedamos con los 8 ultimos digitos
}

nif::operator long() const { 
  return value_;
}

bool nif::operator==(const nif& other) const {
  return value_ == other.value_;
}

bool nif::operator!=(const nif& other) const {
  return value_ != other.value_;
}

bool nif::operator<(const nif& other) const {
  return value_ < other.value_;
}

std::ostream& operator<<(std::ostream& os, const nif& x) {
  os << x.value_;
  return os;
}
