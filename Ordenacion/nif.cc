#include "nif.h"

// Constructor aleatorio: 8 cifras entre 10.000.000 y 99.999.999
nif::nif() {
  value_ = 10000000 + std::rand() % 90000000;
}

nif::nif(long v) : value_(v) {}

nif::operator long() const {
  return value_;
}

// Comparadores básicos
bool nif::operator==(const nif& other) const {
  return value_ == other.value_;
}

bool nif::operator!=(const nif& other) const {
  return value_ != other.value_;
}

bool nif::operator<(const nif& other) const {
  return value_ < other.value_;
}

bool nif::operator>(const nif& other) const {
  return value_ > other.value_;
}

bool nif::operator<=(const nif& other) const {
  return value_ <= other.value_;
}

bool nif::operator>=(const nif& other) const {
  return value_ >= other.value_;
}

// Para imprimir el nif
std::ostream& operator<<(std::ostream& os, const nif& x) {
  os << x.value_;
  return os;
}
