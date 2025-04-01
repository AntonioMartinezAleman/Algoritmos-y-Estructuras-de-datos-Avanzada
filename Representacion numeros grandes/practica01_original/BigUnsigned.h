#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>

class BigUnsigned{ // representa los números no negativos
 public:
  explicit BigUnsigned(unsigned n = 0);
  BigUnsigned(const unsigned char* );
  BigUnsigned(const BigUnsigned&); 

  BigUnsigned& operator=(const BigUnsigned&);

  friend std::ostream& operator<<(std::ostream&, const BigUnsigned&);
  friend std::istream& operator>>(std::istream&, BigUnsigned&);

  bool operator==(const BigUnsigned&) const;
  friend bool operator<(const BigUnsigned&, const BigUnsigned&);
  
  BigUnsigned& operator++(); // Pre-incremento
  BigUnsigned operator++(int); // Post-incremento
  BigUnsigned& operator--(); // Pre-decremento
  BigUnsigned operator--(int); // Post-decremento

  friend BigUnsigned operator+(const BigUnsigned&, const BigUnsigned&);
  BigUnsigned operator-(const BigUnsigned&) const;
  BigUnsigned operator*(const BigUnsigned&) const;
  friend BigUnsigned operator/(const BigUnsigned&, const BigUnsigned&);
  BigUnsigned operator%(const BigUnsigned&) const;
 
 private:
  std::vector<unsigned char> digits;
  void trimLeadingZeros() {
    while (digits.size() > 1 && digits.back() == 0) {
      digits.pop_back();
    }
  }
};