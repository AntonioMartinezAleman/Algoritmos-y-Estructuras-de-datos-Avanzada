#ifndef BIGUNSIGNED_H
#define BIGUNSIGNED_H

#include <iostream>
#include <vector>
#include <stdexcept>

template <unsigned char Base>
class BigUnsigned {
  public:
    BigUnsigned(unsigned n = 0);
    BigUnsigned(const unsigned char* str);
    BigUnsigned(const BigUnsigned<Base>& other);

    BigUnsigned<Base>& operator=(const BigUnsigned<Base>& other);

    template <unsigned char B>
    friend std::ostream& operator<<(std::ostream& os, const BigUnsigned<B>& bu);

    template <unsigned char B>
    friend std::istream& operator>>(std::istream& is, BigUnsigned<B>& bu);

    bool operator==(const BigUnsigned<Base>& other) const;

    template <unsigned char B>
    friend bool operator<(const BigUnsigned<B>& lhs, const BigUnsigned<B>& rhs);

    template <unsigned char B>
    friend BigUnsigned<B> operator+(const BigUnsigned<B>& lhs, const BigUnsigned<B>& rhs);

    BigUnsigned<Base> operator-(const BigUnsigned<Base>& other) const;
    BigUnsigned<Base> operator*(const BigUnsigned<Base>& other) const;

    template <unsigned char B>
    friend BigUnsigned<B> operator/(const BigUnsigned<B>& lhs, const BigUnsigned<B>& rhs);

    BigUnsigned<Base> operator%(const BigUnsigned<Base>& other) const;

  private:
    std::vector<unsigned char> digits;
};

#endif
