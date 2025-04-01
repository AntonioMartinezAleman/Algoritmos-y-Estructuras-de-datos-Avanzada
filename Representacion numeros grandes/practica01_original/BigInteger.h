#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include "BigUnsigned.h"

class BigInteger {
public:
  // Constructores
  BigInteger(int n = 0);
  BigInteger(const BigUnsigned&);
  BigInteger(const BigInteger &other);
  // Operadores de asignación
  BigInteger& operator=(const BigInteger&);

  // Operadores de entrada y salida
  friend std::ostream& operator<<(std::ostream&, const BigInteger&);
  friend std::istream& operator>>(std::istream&, BigInteger&);

  // Comparación
  bool operator==(const BigInteger&) const;
  bool operator<(const BigInteger&) const;

  BigInteger& operator++();
  BigInteger operator++(int);
  BigInteger& operator--();
  BigInteger operator--(int);

  // Operadores aritméticos
  BigInteger operator+(const BigInteger&) const;
  BigInteger operator-(const BigInteger&) const;
  BigInteger operator*(const BigInteger&) const;
  BigInteger operator/(const BigInteger&) const;
  BigInteger operator%(const BigInteger&) const;

private:
  BigUnsigned value; // Parte numérica absoluta
  bool isNegative;   // Signo del número
  void normalizeSign() {
    if (value == BigUnsigned(static_cast<unsigned>(0))) {
      isNegative = false;
    }
  }

};

#endif