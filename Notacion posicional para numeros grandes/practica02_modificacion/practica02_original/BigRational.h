#ifndef BIGRATIONAL_H
#define BIGRATIONAL_H

#include <iostream>
#include <stdexcept>
#include "BigInteger.h"
#include "BigUnsigned.h"

template <unsigned char Base>
class BigRational {
public:
  BigRational(const BigInteger<Base>& num, const BigUnsigned<Base>& den);
  BigRational(const BigRational<Base>& other);
  BigRational<Base>& operator=(const BigRational<Base>& other);

  BigRational<Base>& operator=(const BigRational<Base>& other) {
    if (this != &other) {
      numerator_   = other.numerator_;
      denominator_ = other.denominator_;
    }
    return *this;
  }

  template <unsigned char B>
  friend std::ostream& operator<<(std::ostream& os, const BigRational<B>& r);

  template <unsigned char B>
  friend std::istream& operator>>(std::istream& is, const BigRational<B>& r);

  bool operator==(const BigRational<Base>& other) const;
  bool operator<(const BigRational<Base>& other) const;
  BigRational<Base> operator+(const BigRational<Base>& other) const;
  BigRational<Base> operator-(const BigRational<Base>& other) const;
  BigRational<Base> operator*(const BigRational<Base>& other) const;
  BigRational<Base> operator/(const BigRational<Base>& other) const;


  // MODIFICACION 

  BigRational<Base> media(const std::vector<BigRational<Base>&> vector_rationals) const;




private:
  BigInteger<Base>  numerator_;
  BigUnsigned<Base> denominator_;
  void reduce(); // hace la fraccion lo mas pequeña posible
};

#endif
