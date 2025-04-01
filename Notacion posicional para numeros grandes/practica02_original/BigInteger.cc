#include "BigInteger.h"

template <unsigned char Base>
BigInteger<Base>::BigInteger(int n) : isNegative(n < 0) {
  unsigned temp = (n < 0)
    ? static_cast<unsigned>(-static_cast<long long>(n))
    : static_cast<unsigned>(n);
  value = BigUnsigned<Base>(temp);
  normalizeSign();
}

template <unsigned char Base>
BigInteger<Base>::BigInteger(const BigUnsigned<Base>& bu)
  : value(bu), isNegative(false) {
  normalizeSign();
}

template <unsigned char Base>
BigInteger<Base>::BigInteger(const BigInteger<Base>& other)
  : value(other.value), isNegative(other.isNegative) {
}

template <unsigned char Base>
BigInteger<Base>& BigInteger<Base>::operator=(const BigInteger<Base>& other) {
  if (this != &other) {
    value = other.value;
    isNegative = other.isNegative;
  }
  return *this;
}

template <unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigInteger<Base>& bi) {
  if (bi.isNegative && bi.value != BigUnsigned<Base>(0u)) {
    os << '-';
  }
  os << bi.value;
  return os;
}

template <unsigned char Base>
std::istream& operator>>(std::istream& is, BigInteger<Base>& bi) {
  std::string s;
  is >> s;
  if (s.empty()) {
    bi.value = BigUnsigned<Base>(0u);
    bi.isNegative = false;
    return is;
  }
  bool negative = false;
  size_t startPos = 0;
  if (s[0] == '-') {
    negative = true;
    startPos = 1;
  }
  std::string digits = s.substr(startPos);
  try {
    bi.value = BigUnsigned<Base>((const unsigned char*)digits.c_str());
    bi.isNegative = (negative && (bi.value != BigUnsigned<Base>(0u)));
  } catch(const std::invalid_argument&) {
    is.setstate(std::ios::failbit);
  }
  return is;
}

template <unsigned char Base>
bool BigInteger<Base>::operator==(const BigInteger<Base>& other) const {
  return (isNegative == other.isNegative) && (value == other.value);
}

template <unsigned char Base>
bool BigInteger<Base>::operator<(const BigInteger<Base>& other) const {
  if (isNegative && !other.isNegative) return true;
  if (!isNegative && other.isNegative) return false;
  if (isNegative && other.isNegative) {
    return (other.value < value);
  } else {
    return (value < other.value);
  }
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator+(const BigInteger<Base>& other) const {
  BigInteger<Base> result;
  if (isNegative == other.isNegative) {
    result.value = value + other.value;
    result.isNegative = isNegative;
  } else {
    if (value < other.value) {
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

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator-(const BigInteger<Base>& other) const {
  BigInteger<Base> negB = other;
  negB.isNegative = !negB.isNegative;
  return *this + negB;
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator*(const BigInteger<Base>& other) const {
  BigInteger<Base> result;
  result.value = value * other.value;
  result.isNegative = (isNegative != other.isNegative)
    && (result.value != BigUnsigned<Base>(0u));
  result.normalizeSign();
  return result;
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator/(const BigInteger<Base>& other) const {
  if (other.value == BigUnsigned<Base>(0u)) {
    throw std::invalid_argument("División por cero");
  }
  BigInteger<Base> result;
  result.value = value / other.value;
  result.isNegative = (isNegative != other.isNegative)
    && (result.value != BigUnsigned<Base>(0u));
  result.normalizeSign();
  return result;
}

template <unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator%(const BigInteger<Base>& other) const {
  if (other.value == BigUnsigned<Base>(0u)) {
    throw std::invalid_argument("División por cero (mod)");
  }
  BigInteger<Base> result;
  result.value = value % other.value;
  result.isNegative = isNegative;
  result.normalizeSign();
  return result;
}

BigInteger<2>::BigInteger(long long n) {
  fromLongLong(n);
}

BigInteger<2>::BigInteger(const BigInteger<2>& other) {
  bits = other.bits;
}

BigInteger<2>& BigInteger<2>::operator=(const BigInteger<2>& other) {
  if (this != &other) {
    bits = other.bits;
  }
  return *this;
}

std::ostream& operator<<(std::ostream& os, const BigInteger<2>& bi) {
  if (bi.bits.empty()) {
    os << '0';
    return os;
  }
  for (int i = static_cast<int>(bi.bits.size()) - 1; i >= 0; --i) {
    os << (bi.bits[i] ? '1' : '0');
  }
  return os;
}

std::istream& operator>>(std::istream& is, BigInteger<2>& bi) {
  std::string s;
  is >> s;
  try {
    bi.fromString(s);
  } catch(const std::invalid_argument&) {
    is.setstate(std::ios::failbit);
  }
  return is;
}

bool BigInteger<2>::operator==(const BigInteger<2>& other) const {
  return (bits == other.bits);
}

bool BigInteger<2>::operator<(const BigInteger<2>& other) const {
  return this->toLongLong() < other.toLongLong();
}

BigInteger<2> BigInteger<2>::operator+(const BigInteger<2>& other) const {
  BigInteger<2> result(*this);
  result.add(other);
  return result;
}

BigInteger<2> BigInteger<2>::operator-(const BigInteger<2>& other) const {
  BigInteger<2> negB(other);
  negB.toTwosComplement();
  BigInteger<2> result(*this);
  result.add(negB);
  return result;
}

void BigInteger<2>::fromLongLong(long long n) {
  bits.clear();
  if (n == 0) {
    bits.push_back(false);
    return;
  }
  bool negative = (n < 0);
  unsigned long long posVal = (negative ? static_cast<unsigned long long>(-n)
                                        : static_cast<unsigned long long>(n));
  while (posVal > 0) {
    bool bit = (posVal & 1ULL) != 0;
    bits.push_back(bit);
    posVal >>= 1ULL;
  }
  if (!negative) {
    if (bits.back()) {
      bits.push_back(false);
    }
  } else {
    toTwosComplement();
  }
  trimLeading();
}

long long BigInteger<2>::toLongLong() const {
  if (bits.empty()) return 0;
  bool signBit = bits.back();
  BigInteger<2> temp(*this);
  if (signBit) {
    temp.fromTwosComplement();
    unsigned long long mag = temp.toULL();
    if (mag > 9223372036854775808ULL) {
      return -9223372036854775807LL;
    }
    return -static_cast<long long>(mag);
  } else {
    unsigned long long mag = temp.toULL();
    if (mag > 9223372036854775807ULL) {
      return 9223372036854775807LL;
    }
    return static_cast<long long>(mag);
  }
}

void BigInteger<2>::toTwosComplement() {
  for (size_t i = 0; i < bits.size(); ++i) {
    bits[i] = !bits[i];
  }
  bool carry = true;
  for (size_t i = 0; i < bits.size() && carry; i++) {
    bool old = bits[i];
    bits[i] = old ^ carry;
    carry = (old && carry);
  }
  if (carry) {
    bits.push_back(true);
  }
  if (!bits.empty() && !bits.back()) {
    bits.push_back(true);
  }
  trimLeading();
}

void BigInteger<2>::fromTwosComplement() {
  bool borrow = true;
  for (size_t i = 0; i < bits.size() && borrow; i++) {
    bool old = bits[i];
    bits[i] = old ^ borrow;
    borrow = (!old && borrow);
  }
  for (size_t i = 0; i < bits.size(); ++i) {
    bits[i] = !bits[i];
  }
  if (!bits.empty() && bits.back()) {
    bits.push_back(false);
  }
  trimLeading();
}

unsigned long long BigInteger<2>::toULL() const {
  unsigned long long result = 0;
  unsigned long long place = 1;
  for (size_t i = 0; i < bits.size(); i++) {
    if (bits[i]) {
      result += place;
    }
    place <<= 1ULL;
  }
  return result;
}

void BigInteger<2>::add(const BigInteger<2>& other) {
  size_t maxSize = std::max(bits.size(), other.bits.size());
  bool carry = false;
  for (size_t i = 0; i < maxSize || carry; i++) {
    if (i == bits.size()) {
      bits.push_back(false);
    }
    bool a = bits[i];
    bool b = (i < other.bits.size()) ? other.bits[i] : false;
    bool sum = (a ^ b) ^ carry;
    carry = ((a && b) || (a && carry) || (b && carry));
    bits[i] = sum;
  }
  if (!bits.back()) {
    bits.push_back(false);
  } else {
    bits.push_back(true);
  }
  trimLeading();
}

void BigInteger<2>::addOne() {
  bool carry = true;
  for (size_t i = 0; i < bits.size() && carry; i++) {
    bool old = bits[i];
    bits[i] = old ^ carry;
    carry = (old && carry);
  }
  if (carry) {
    bits.push_back(true);
  }
  if (!bits.empty()) {
    bits.push_back(bits.back());
  }
  trimLeading();
}

void BigInteger<2>::subOne() {
  bool borrow = true;
  for (size_t i = 0; i < bits.size() && borrow; i++) {
    bool old = bits[i];
    bits[i] = old ^ borrow;
    borrow = (!old && borrow);
  }
  if (borrow) {
    bits.push_back(true);
  }
  if (!bits.empty()) {
    bits.push_back(bits.back());
  }
  trimLeading();
}

void BigInteger<2>::trimLeading() {
  while (bits.size() > 1) {
    bool top = bits.back();
    bool next = bits[bits.size() - 2];
    if (top == next) {
      bits.pop_back();
    } else {
      break;
    }
  }
  if (bits.empty()) {
    bits.push_back(false);
  }
}

void BigInteger<2>::fromString(const std::string &s) {
  bits.clear();
  if (s.empty()) {
    bits.push_back(false);
    return;
  }
  for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i) {
    char c = s[i];
    if (c == '0') {
      bits.push_back(false);
    } else if (c == '1') {
      bits.push_back(true);
    } else {
      throw std::invalid_argument("Cadena binaria no válida");
    }
  }
  bool signBit = bits.back();
  bits.push_back(signBit);
  trimLeading();
}

template class BigInteger<2>;
