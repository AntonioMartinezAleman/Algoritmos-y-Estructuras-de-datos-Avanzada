#include <iostream>
#include <string>
#include "BigInteger.h"
#include "BigUnsigned.h"

static std::string trim(const std::string &s) {
  size_t i = 0;
  while (i < s.size() && isspace((unsigned char)s[i])) i++;
  size_t j = s.size();
  while (j > i && isspace((unsigned char)s[j - 1])) j--;
  return s.substr(i, j - i);
}

int main() {

  std::string baseLine;
  std::getline(std::cin, baseLine);
  std::cout << baseLine << "\n";
  std::string n1Line;
  std::getline(std::cin, n1Line);
  std::cout << n1Line << "\n";
  std::string n2Line;
  std::getline(std::cin, n2Line);
  std::cout << n2Line << "\n";
  int baseVal = 10;
  {
    auto p = baseLine.find("=");
    if (p != std::string::npos) {
      baseVal = std::stoi(trim(baseLine.substr(p + 1)));
    }
  }
  auto parseFraction = [&](const std::string &s) {
    auto p = s.find("=");
    auto fraction = trim(s.substr(p + 1));
    p = fraction.find("/");
    std::string numPart = trim(fraction.substr(0, p));
    std::string denPart = trim(fraction.substr(p + 1));
    BigInteger<10> num(numPart.c_str());
    BigUnsigned<10> den(denPart.c_str());
    return BigRational<10>(num, den);
  };
  BigRational<10> N1 = parseFraction(n1Line);
  BigRational<10> N2 = parseFraction(n2Line);
  std::cout << "N1 == N2: " << (N1 == N2 ? "true" : "false") << "\n";
  std::cout << "N1 < N2: " << (N1 < N2 ? "true" : "false") << "\n";
  std::cout << "N1+N2: " << (N1 + N2) << "\n";
  std::cout << "N1-N2: " << (N1 - N2) << "\n";
  std::cout << "N1*N2: " << (N1 * N2) << "\n";
  try {
    std::cout << "N1/N2: " << (N1 / N2) << "\n";
  } catch (...) {
    std::cout << "N1/N2: error\n";
  }
  return 0;
}
