#include <iostream>
#include "BigInteger.h"

BigInteger mcd(const BigInteger &a, const BigInteger &b) {
  if (b == BigInteger(0)) {
    return a;
  }
  return mcd(b, a % b);
}

int main() {

  BigInteger a, b;

  a = 400;
  b = 100;

  std::cout << a + b << std::endl;
  std::cout << a - b << std::endl;
  std::cout << a * b << std::endl;
  std::cout << a / b << std::endl;
  std::cout << a % b << std::endl;

  BigInteger result = mcd(a, b);


  std::cout << "El MCD de " << a << " y " << b << " es: " << result << std::endl;

  return 0;
}