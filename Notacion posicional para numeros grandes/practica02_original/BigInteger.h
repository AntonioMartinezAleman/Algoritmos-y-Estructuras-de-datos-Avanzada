#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <iosfwd>
#include <string>
#include <cstdint>
#include "BigUnsigned.h"

template <unsigned char Base>
class BigInteger {
 public:
  BigInteger(int n = 0);
  BigInteger(const BigUnsigned<Base>& bu);
  BigInteger(const BigInteger<Base>& other);
  BigInteger<Base>& operator=(const BigInteger<Base>& other);

  template <unsigned char B>
  friend std::ostream& operator<<(std::ostream& os, const BigInteger<B>& bi);

  template <unsigned char B>
  friend std::istream& operator>>(std::istream& is, BigInteger<B>& bi);

  bool operator==(const BigInteger<Base>& other) const;
  bool operator<(const BigInteger<Base>& other) const;

  BigInteger<Base> operator+(const BigInteger<Base>& other) const;
  BigInteger<Base> operator-(const BigInteger<Base>& other) const;
  BigInteger<Base> operator*(const BigInteger<Base>& other) const;
  BigInteger<Base> operator/(const BigInteger<Base>& other) const;
  BigInteger<Base> operator%(const BigInteger<Base>& other) const;

 private:
  BigUnsigned<Base> value;
  bool isNegative;

  void normalizeSign() {
    if (value == BigUnsigned<Base>(0u)) {
      isNegative = false;
    }
  }
};

template <>
class BigInteger<2> {
public:
  BigInteger<2>(long long n = 0);
  BigInteger<2>(const BigInteger<2>& other);
  BigInteger<2>& operator=(const BigInteger<2>& other);

  friend std::ostream& operator<<(std::ostream& os, const BigInteger<2>& bi);
  friend std::istream& operator>>(std::istream& is, BigInteger<2>& bi);

  bool operator==(const BigInteger<2>& other) const;
  bool operator<(const BigInteger<2>& other) const;

  BigInteger<2> operator+(const BigInteger<2>& other) const;
  BigInteger<2> operator-(const BigInteger<2>& other) const;

private:
  std::vector<bool> bits;

  void fromLongLong(long long n);
  long long toLongLong() const;
  void toTwosComplement();
  void fromTwosComplement();
  unsigned long long toULL() const;
  void add(const BigInteger<2>& other);
  void addOne();
  void subOne();
  void trimLeading();
  void fromString(const std::string &s);
};

#endif
