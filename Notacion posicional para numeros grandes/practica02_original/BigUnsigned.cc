#include "BigUnsigned.h"
#include <algorithm>
#include <string>

template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(unsigned n) {
  digits.clear();
  if (n == 0) {
    digits.push_back(0);
  } else {
    while (n > 0) {
      digits.push_back(n % Base);
      n /= Base;
    }
  }
}

template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(const unsigned char* str) {
  digits.clear();
  size_t len = 0;
  while (str[len] != '\0') {
    ++len;
  }
  for (int i = static_cast<int>(len) - 1; i >= 0; --i) {
    unsigned char c = str[i];
    unsigned digitValue = 0;
    if (c >= '0' && c <= '9') {
      digitValue = c - '0';
    } else if (c >= 'A' && c <= 'F') {
      digitValue = c - 'A' + 10;
    } else if (c >= 'a' && c <= 'f') {
      digitValue = c - 'a' + 10;
    } else {
      throw std::invalid_argument("Caracter inválido para la base proporcionada.");
    }
    if (digitValue >= Base) {
      throw std::invalid_argument("Valor de dígito fuera de rango para la base proporcionada.");
    }
    digits.push_back(static_cast<unsigned char>(digitValue));
  }
  if (digits.empty()) {
    digits.push_back(0);
  }
}

template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(const BigUnsigned<Base>& other) {
  digits = other.digits;
}

template <unsigned char Base> 
BigUnsigned<Base>& BigUnsigned<Base>::operator=(const BigUnsigned<Base>& other) {

  if (this != &other) {
    digits = other.digits;
  }
  return *this;
}

template <unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigUnsigned<Base>& bu) {
  if (bu.digits.empty()) {
    os << 0;
    return os;
  }
  int i = static_cast<int>(bu.digits.size()) - 1;
  while (i > 0 && bu.digits[i] == 0) {
    i--;
  }
  for (; i >= 0; --i) {
    unsigned char digitValue = bu.digits[i];
    if (digitValue < 10) {
      os << static_cast<char>(digitValue + '0');
    } else {
      os << static_cast<char>((digitValue - 10) + 'A');
    }
  }
  return os;
}

template <unsigned char Base>
std::istream& operator>>(std::istream& is, BigUnsigned<Base>& bu) {
  std::string input;
  is >> input;
  bu.digits.clear();
  for (int i = static_cast<int>(input.size()) - 1; i >= 0; --i) {
    unsigned char c = input[i];
    unsigned digitValue = 0;
    if (c >= '0' && c <= '9') {
      digitValue = c - '0';
    } else if (c >= 'A' && c <= 'F') {
      digitValue = c - 'A' + 10;
    } else if (c >= 'a' && c <= 'f') {
      digitValue = c - 'a' + 10;
    } else {
      throw std::invalid_argument("Caracter inválido para la base proporcionada.");
    }
    if (digitValue >= Base) {
      throw std::invalid_argument("Valor de dígito fuera de rango para la base proporcionada.");
    }
    bu.digits.push_back(static_cast<unsigned char>(digitValue));
  }
  if (bu.digits.empty()) {
    bu.digits.push_back(0);
  }
  return is;
}

template <unsigned char Base>
bool BigUnsigned<Base>::operator==(const BigUnsigned<Base>& other) const {
  return digits == other.digits;
}

template <unsigned char Base>
bool operator<(const BigUnsigned<Base>& lhs, const BigUnsigned<Base>& rhs) {
  if (lhs.digits.size() < rhs.digits.size()) return true;
  if (lhs.digits.size() > rhs.digits.size()) return false;
  for (int i = static_cast<int>(lhs.digits.size()) - 1; i >= 0; --i) {
    if (lhs.digits[i] < rhs.digits[i]) return true;
    if (lhs.digits[i] > rhs.digits[i]) return false;
  }
  return false;
}

template <unsigned char Base>
BigUnsigned<Base> operator+(const BigUnsigned<Base>& lhs, const BigUnsigned<Base>& rhs) {
  BigUnsigned<Base> result;
  result.digits.clear();
  unsigned carry = 0;
  size_t maxSize = std::max(lhs.digits.size(), rhs.digits.size());
  for (size_t i = 0; i < maxSize || carry; i++) {
    unsigned sum = carry;
    if (i < lhs.digits.size()) sum += lhs.digits[i];
    if (i < rhs.digits.size()) sum += rhs.digits[i];
    carry = sum / Base;
    result.digits.push_back(sum % Base);
  }
  return result;
}

template <unsigned char Base>
BigUnsigned<Base> BigUnsigned<Base>::operator-(const BigUnsigned<Base>& other) const {
  if (*this < other) {
    throw std::invalid_argument("Resultado negativo en BigUnsigned.");
  }
  BigUnsigned<Base> result;
  result.digits.clear();
  unsigned borrow = 0;
  for (size_t i = 0; i < digits.size(); i++) {
    int diff = digits[i] - borrow;
    if (i < other.digits.size()) {
      diff -= other.digits[i];
    }
    if (diff < 0) {
      diff += Base;
      borrow = 1;
    } else {
      borrow = 0;
    }
    result.digits.push_back(static_cast<unsigned char>(diff));
  }
  while (result.digits.size() > 1 && result.digits.back() == 0) {
    result.digits.pop_back();
  }
  return result;
}

template class BigUnsigned<2>;
template class BigUnsigned<8>;
template class BigUnsigned<10>;
template class BigUnsigned<16>;