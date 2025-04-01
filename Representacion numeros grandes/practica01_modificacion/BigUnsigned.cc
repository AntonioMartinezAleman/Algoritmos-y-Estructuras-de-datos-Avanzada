#include "BigUnsigned.h"

BigUnsigned::BigUnsigned(unsigned n) { //numero a reverse vector
  while (n > 0) {
    digits.push_back(n%10);
    n /= 10;
  } if (digits.empty()) {
    digits.push_back(0);
  }
}

BigUnsigned::BigUnsigned(const unsigned char* str) { // cadena de char a reverse vector
  int len = 0;
  while (str[len] != '\0') { // Encontrar el carácter de fin de palabra
    ++len;
  }
  for (int i = len - 1; i >= 0; --i) {
    digits.push_back(str[i] - '0');
  }
}


BigUnsigned::BigUnsigned(const BigUnsigned& other) { //constructor de copia
  digits = other.digits;
}

BigUnsigned& BigUnsigned::operator=(const BigUnsigned& other) { //operador de asignacion
  if(this != &other) {
    digits = other.digits;
  }
  return *this;
}

std::ostream& operator<<(std::ostream& os, const BigUnsigned& num) { // print vector
  // Si el número es 0, imprimir un solo "0"
  if (num.digits.size() == 1 && num.digits[0] == 0) {
    os << "0";
    return os;
  }
  
  // Imprimir en orden correcto
  for (auto it = num.digits.rbegin(); it != num.digits.rend(); ++it) {
    os << static_cast<char>(*it + '0');
  }
  return os;
}

std::istream& operator>>(std::istream& is, BigUnsigned& num) { //entrada a reverse vector
  std::string input;
  is >> input;
  num.digits.clear();
  for (int i = input.size() - 1; i >= 0; i--) {
    num.digits.push_back(input[i] - '0');
  }
  return is;
}

bool BigUnsigned::operator==(const BigUnsigned& other) const {
  return digits == other.digits;
}

bool operator<(const BigUnsigned& a, const BigUnsigned& b) {
  if (a.digits.size() != b.digits.size()) {
    return a.digits.size() < b.digits.size();
  } 
  for (int i = a.digits.size() - 1; i >= 0; i--) {
    if (a.digits[i] != b.digits[i]) {
      return a.digits[i] < b.digits[i];
    }
  }
  return false; // si son iguales
}

BigUnsigned& BigUnsigned::operator++() { //pre
  for (size_t i = 0; i < digits.size(); i++) {
    if (digits[i] != 9) {
      digits[i]++;
      return *this;
    } else {
      digits[i] = 0;
    }
  }
  digits.push_back(1);
  return *this;
}

BigUnsigned BigUnsigned::operator++(int) { //pos
  BigUnsigned temp = *this;
  ++(*this);
  return temp;
}

BigUnsigned& BigUnsigned::operator--() { //pre
  if (digits.size() == 1 && digits[0] == 0) {
    throw std::underflow_error("BigUnsigned no puede ser negativo");
  }
  for (size_t i = 0; i < digits.size(); i++) {
    if (digits[i] != 0) {
      digits[i]--;
      break;
    } else {
      digits[i] = 9;
    }
  }
  if (digits.back() == 0 && digits.size() > 1) {
    digits.pop_back();
  }
  return *this;
}

BigUnsigned BigUnsigned::operator--(int) { //pos
  if (digits.size() == 1 && digits[0] == 0) {
    throw std::underflow_error("BigUnsigned no puede ser negativo");
  }
  BigUnsigned temp = *this;
  --(*this);
  return temp;
}

BigUnsigned operator+(const BigUnsigned& a, const BigUnsigned& b) { // suma como en papel, con carry
  BigUnsigned result;
  unsigned int carry = 0;
  size_t maxSize = std::max(a.digits.size(), b.digits.size());
  result.digits.clear();
  for (size_t i = 0; i < maxSize; i++) {
      unsigned int digitA = (i < a.digits.size()) ? a.digits[i] : 0;
      unsigned int digitB = (i < b.digits.size()) ? b.digits[i] : 0;
      unsigned int sum = digitA + digitB + carry;

      result.digits.push_back(sum % 10); // Guardamos solo el dígito de unidades
      carry = sum / 10; // Calculamos el acarreo
  }

  if (carry > 0) {
      result.digits.push_back(carry);
  }

  result.trimLeadingZeros(); // Eliminar ceros innecesarios
  return result;
}

BigUnsigned BigUnsigned::operator-(const BigUnsigned& other) const {
  if (*this < other) {
    throw std::underflow_error("BigUnsigned no puede ser negativo");
  }
  BigUnsigned result;
  result.digits.resize(digits.size());
  int borrow = 0; //prestamo como en resta a papel
  for (size_t i = 0; i < digits.size(); i++) {
    int digitA = digits[i];
    int digitB = (i < other.digits.size()) ? other.digits[i] : 0;
    int sub = digitA - digitB - borrow;
    if (sub < 0) {  // Necesita préstamo
      sub += 10;    // ajuste del valor
      borrow = 1;   // prestamos
    } else {
      borrow = 0;   // No hay préstamo
    }

    result.digits[i] = sub; 
  }
  result.trimLeadingZeros();
  return result;
}

BigUnsigned BigUnsigned::operator*(const BigUnsigned& other) const {
  BigUnsigned zero = BigUnsigned(static_cast<unsigned>(0)); // Forzar constructor
  if (*this == zero || other == zero) { // si uno es cero el otro tambien
      return zero;
  }
  BigUnsigned result;
  result.digits.resize(digits.size() + other.digits.size(), 0);
  for (size_t i = 0; i < digits.size(); i++) {
    unsigned char carry = 0;
    for (size_t j = 0; j < other.digits.size(); j++) {
      int product = digits[i] * other.digits[j] + result.digits[i + j] + carry;
      result.digits[i + j] = product % 10;
      carry = product / 10;
    }
    result.digits[i + other.digits.size()] += carry;
  }
  result.trimLeadingZeros();
  return result;
}

BigUnsigned operator/(const BigUnsigned& dividend, const BigUnsigned& divisor) {
  if (divisor == BigUnsigned(static_cast<unsigned>(0))) {
    throw std::overflow_error("División por cero no permitida.");
  }
  BigUnsigned quotient, remainder;
  for (int i = dividend.digits.size() - 1; i >= 0; --i) {
    remainder.digits.insert(remainder.digits.begin(), dividend.digits[i]);
    while (remainder.digits.size() > 1 && remainder.digits.back() == 0) {
      remainder.digits.pop_back();
    }
    unsigned char count = 0;
    while (!(remainder < divisor)) { //calculo del numero de veces que se puede restar
      remainder = remainder - divisor;
      count++;
    }
    quotient.digits.insert(quotient.digits.begin(), count);
  }
  quotient.trimLeadingZeros();
  return quotient;
}

BigUnsigned BigUnsigned::operator%(const BigUnsigned& divisor) const {
  if (divisor == BigUnsigned(static_cast<unsigned>(0))) {
    throw std::overflow_error("Módulo por cero no permitido.");
  }
  BigUnsigned remainder;
  for (int i = digits.size() - 1; i >= 0; --i) {
    remainder.digits.insert(remainder.digits.begin(), digits[i]);
    while (remainder.digits.size() > 1 && remainder.digits.back() == 0) {
      remainder.digits.pop_back();
    }
    while (!(remainder < divisor)) {
      remainder = remainder - divisor;
    }
  }
  remainder.trimLeadingZeros();
  return remainder;
}