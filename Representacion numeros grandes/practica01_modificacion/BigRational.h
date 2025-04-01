#include "BigInteger.h"

class BigRational {
  public:
  BigRational(int n, int d);

  friend std::ostream& operator<<(std::ostream&, const BigUnsigned&);

  private:
  BigUnsigned numerador;
  BigUnsigned denominador;
  bool IsNegative;
};