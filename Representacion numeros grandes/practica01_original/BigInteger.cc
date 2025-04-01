#include "BigInteger.h"
#include <stdexcept>

BigInteger::BigInteger(int n) {
  if (n == 0) {
    isNegative = false;
    value = BigUnsigned(static_cast<unsigned>(0));
  } else if (n < 0) {
    isNegative = true;
    unsigned int absValue = static_cast<unsigned int>(-static_cast<long long>(n));
    value = BigUnsigned(absValue);
  } else {
    isNegative = false;
    value = BigUnsigned(static_cast<unsigned>(n));
  }
}

BigInteger::BigInteger(const BigUnsigned &bigUn) : value(bigUn), isNegative(false) {
  normalizeSign();
}

BigInteger::BigInteger(const BigInteger &other)
  : value(other.value), isNegative(other.isNegative) {
}

BigInteger &BigInteger::operator=(const BigInteger &other) {
  if (this != &other) {
    value = other.value;
    isNegative = other.isNegative;
  }
  return *this;
}

std::ostream &operator<<(std::ostream &os, const BigInteger &bigInt) {
  if (bigInt.isNegative && !(bigInt.value == BigUnsigned(static_cast<unsigned>(0)))) {
    os << '-';
  }
  os << bigInt.value;
  return os;
}

std::istream &operator>>(std::istream &is, BigInteger &bigInt) {
  std::string temp;
  is >> temp;
  if (!is) {
    return is;
  }
  bool neg = false;
  size_t startPos = 0;
  if (!temp.empty()) {
    if (temp[0] == '-') {
      neg = true;
      startPos = 1;
    } else if (temp[0] == '+') {
      startPos = 1;
    }
  }
  std::string digits = temp.substr(startPos);
  if (digits.empty()) {
    bigInt.value = BigUnsigned(static_cast<unsigned>(0));
    bigInt.isNegative = false;
    return is;
  }
  bigInt.value = BigUnsigned((const unsigned char *)digits.c_str());
  bigInt.isNegative = neg;
  bigInt.normalizeSign();
  return is;
}

bool BigInteger::operator==(const BigInteger &other) const {
  return (isNegative == other.isNegative) && (value == other.value);
}

bool BigInteger::operator<(const BigInteger &other) const {
  if (isNegative && !other.isNegative) {
    return true;
  }
  if (!isNegative && other.isNegative) {
    return false;
  }
  if (!isNegative && !other.isNegative) {
    return value < other.value;
  } else {
    return other.value < value;
  }
}

BigInteger BigInteger::operator+(const BigInteger &other) const {
  BigInteger result;
  if (isNegative == other.isNegative) {
    result.value = value + other.value;
    result.isNegative = isNegative;
  } else {
    if (value == other.value) {
      result.value = BigUnsigned(static_cast<unsigned>(0));
      result.isNegative = false;
    } else if (value < other.value) {
      result.value = other.value - value;
      result.isNegative = other.isNegative;
    } else {
      result.value = value - other.value;
      result.isNegative = isNegative;
    }
  }
  result.normalizeSign();
  return result;
}

BigInteger BigInteger::operator-(const BigInteger &other) const {
  BigInteger temp = other;
  temp.isNegative = !temp.isNegative;
  return *this + temp;
}

BigInteger BigInteger::operator*(const BigInteger &other) const {
  BigInteger result;
  result.value = value * other.value;
  result.isNegative = (isNegative != other.isNegative);
  result.normalizeSign();
  return result;
}

BigInteger BigInteger::operator/(const BigInteger &other) const {
  if (other.value == BigUnsigned(static_cast<unsigned>(0))) {
    throw std::overflow_error("Division by zero not permitted.");
  }
  BigInteger result;
  result.value = value / other.value;
  result.isNegative = (isNegative != other.isNegative);
  result.normalizeSign();
  return result;
}

BigInteger BigInteger::operator%(const BigInteger &other) const {
  if (other.value == BigUnsigned(static_cast<unsigned>(0))) {
    throw std::overflow_error("Modulo by zero not permitted.");
  }
  BigInteger result;
  result.value = value % other.value;
  result.isNegative = isNegative;
  result.normalizeSign();
  return result;
}

BigInteger& BigInteger::operator++() {
  BigInteger one(1);
  *this = *this + one;
  return *this;
}

BigInteger BigInteger::operator++(int) {
  BigInteger temp(*this);
  ++(*this);
  return temp;
}

BigInteger& BigInteger::operator--() {
  BigInteger one(1);
  *this = *this - one;
  return *this;
}

BigInteger BigInteger::operator--(int) {
  BigInteger temp(*this);
  --(*this);
  return temp;
}