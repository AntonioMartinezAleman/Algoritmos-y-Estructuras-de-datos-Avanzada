#include "BigRational.h"

BigRational::BigRational(int n, int d) {
  denominador = n;
  denominador = d;
  if (n == 0 || d == 0) {
  }
}


std::ostream& operator<<(std::ostream& os, const BigRational& rational) {
  if (rational.isNegative) {
    os << '-';
  }
  os << rational.numerador << " / " << rational.denominador;
  return os;
}