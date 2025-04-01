#include "BigRational.h"
#include <stdexcept>

template <unsigned char Base>
BigRational<Base>::BigRational(const BigInteger<Base>& num, const BigUnsigned<Base>& den)
  : numerator_(num), denominator_(den) {
  if (denominator_ == BigUnsigned<Base>(0u)) {
    throw std::invalid_argument("Denominator cannot be zero.");
  }
  reduce();
}

template <unsigned char Base>
BigRational<Base>::BigRational(const BigRational<Base>& other)
  : numerator_(other.numerator_), denominator_(other.denominator_)
{
}

template <unsigned char Base>
BigRational<Base>& BigRational<Base>::operator=(const BigRational<Base>& other) {
  if (this != &other) {
    numerator_   = other.numerator_;
    denominator_ = other.denominator_;
  }
  return *this;
}


template <unsigned char Base>
bool BigRational<Base>::operator==(const BigRational<Base>& other) const {
  return (numerator_ * BigInteger<Base>(other.denominator_)) 
       == (other.numerator_ * BigInteger<Base>(denominator_));
}

template <unsigned char Base>
bool BigRational<Base>::operator<(const BigRational<Base>& other) const {
  BigInteger<Base> cross1 = numerator_ * BigInteger<Base>(other.denominator_);
  BigInteger<Base> cross2 = other.numerator_ * BigInteger<Base>(denominator_);
  return cross1 < cross2;
}

template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator+(const BigRational<Base>& other) const {
  BigInteger<Base> newNum =
      numerator_ * BigInteger<Base>(other.denominator_)
    + other.numerator_ * BigInteger<Base>(denominator_);

  BigUnsigned<Base> newDen = denominator_ * other.denominator_;

  BigRational<Base> result(BigInteger<Base>(newNum), newDen);
  return result;
}

template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator-(const BigRational<Base>& other) const {
  BigInteger<Base> newNum =
      numerator_ * BigInteger<Base>(other.denominator_)
    - other.numerator_ * BigInteger<Base>(denominator_);

  BigUnsigned<Base> newDen = denominator_ * other.denominator_;

  BigRational<Base> result(BigInteger<Base>(newNum), newDen);
  return result;
}

template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator*(const BigRational<Base>& other) const {
  BigInteger<Base> newNum = numerator_ * other.numerator_;
  BigUnsigned<Base> newDen = denominator_ * other.denominator_;

  BigRational<Base> result(newNum, newDen);
  return result;
}

template <unsigned char Base>
BigRational<Base> BigRational<Base>::operator/(const BigRational<Base>& other) const {
  if (other.numerator_ == BigInteger<Base>(0)) {
    throw std::runtime_error("Division by zero in BigRational");
  }
  BigInteger<Base> newNum = numerator_ * BigInteger<Base>(other.denominator_);
  BigInteger<Base> absNumOther = other.numerator_;
  bool negative = false;
  if (absNumOther < BigInteger<Base>(0)) {
    negative = true;
    absNumOther = absNumOther * BigInteger<Base>(-1); 
  }

  BigUnsigned<Base> absNumOtherU(absNumOther); 
  BigUnsigned<Base> newDen = denominator_ * absNumOtherU;
  if (negative) {
    newNum = newNum * BigInteger<Base>(-1);
  }
  BigRational<Base> result(newNum, newDen);
  return result;
}

template <unsigned char Base>
void BigRational<Base>::reduce() {
  if (denominator_ == BigUnsigned<Base>(0u)) {
    throw std::invalid_argument("Denominator cannot be zero.");
  }
  BigInteger<Base> tmpNum = numerator_;
  bool wasNegative = false;
  if (tmpNum < BigInteger<Base>(0)) {
    wasNegative = true;
    tmpNum = tmpNum * BigInteger<Base>(-1);
  }
  BigUnsigned<Base> gcdVal = gcd<Base>(BigUnsigned<Base>(tmpNum), denominator_);
  BigInteger<Base> gcdAsInt(gcdVal);
  numerator_ = numerator_ / gcdAsInt;
  denominator_ = denominator_ / gcdVal;
  if (wasNegative) {
    numerator_ = numerator_ * BigInteger<Base>(-1);
  }
}

template class BigRational<2>;
template class BigRational<8>;
template class BigRational<10>;
template class BigRational<16>;