//Language: C++
//by Rahul Balamwar

#include <iostream>
#include <set>
#include <climits>


#ifdef ORIGINAL


unsigned int digitSum(unsigned long long x)
{
  unsigned int result = 0;
  while (x > 0)
  {
    result += x % 10;
    x      /= 10;
  }
  return result;
}

int main()
{
  std::set<unsigned long long> solutions;

  
  unsigned int MaxBase = 20 * 9;
  // base is the sum of all digits
  for (unsigned int base = 2; base <= MaxBase; base++)
  {
    unsigned int exponent = 1;
    
    unsigned long long current = base;

    while (current < ULLONG_MAX / base) // 1^64 - 1
    {
      auto sum = digitSum(current);
      
      if (sum == base && current >= 10)
        solutions.insert(current);

      
      current *= base;
      exponent++;
    }
  }

 
  auto i = solutions.begin();
  
  std::advance(i, 30 - 1);
  
  std::cout << *i << std::endl;
  return 0;
}

#else

#include <vector>


struct BigNum : public std::vector<unsigned int>
{
  unsigned int maxDigit;

 
  BigNum(unsigned long long x = 0, unsigned int base = 10)
  : maxDigit(base)
  {
    do
    {
      push_back(x % maxDigit);
      x /= maxDigit;
    } while (x > 0);
  }

  // add two big numbers
  void operator+=(const BigNum& other)
  {
    
    if (size() < other.size())
      resize(other.size(), 0);

    unsigned int carry = 0;
    for (unsigned int i = 0; i < size(); i++)
    {
      carry += operator[](i);
      if (i < other.size())
        carry += other[i];
      else
        if (carry == 0)
          return;

      if (carry < maxDigit)
      {
        // no overflow
        operator[](i) = carry;
        carry = 0;
      }
      else
      {
        
        operator[](i) = carry - maxDigit;
        carry = 1;
      }
    }

    if (carry > 0)
      push_back(carry);
  }

  
  void operator*=(unsigned int factor)
  {
    unsigned long long carry = 0;
    for (size_t i = 0; i < size(); i++)
    {
      carry += operator[](i) * (unsigned long long)factor;
      operator[](i) = carry % maxDigit;
      carry /= maxDigit;
    }
    // store remaining carry in new digits
    while (carry > 0)
    {
      push_back(carry % maxDigit);
      carry /= maxDigit;
    }
  }

  
  bool operator<(const BigNum& other) const
  {
    if (size() < other.size())
      return true;
    if (size() > other.size())
      return false;
    for (int i = (int)size() - 1; i >= 0; i--)
    {
      if (operator[](i) < other[i])
        return true;
      if (operator[](i) > other[i])
        return false;
    }
    return false;
  }

  
  BigNum convert(unsigned int newRadix) const
  {
    BigNum result(0, newRadix);
    for (auto i = rbegin(); i != rend(); i++)
    {
      result *= maxDigit;
      result += *i;
    }
    return result;
  }
};


// add all digits
unsigned int digitSum(const BigNum& x)
{
  unsigned int result = 0;
  for (auto digit : x)
    result += digit;
  return result;
}


int main()
{
  std::set<BigNum> solutions;
  unsigned int radix = 10;
  std::cin >> radix;

  
  BigNum googol(1, 10);
  for (unsigned int digits = 1; digits <= 100; digits++)
    googol *= 10;
  
  BigNum max = googol.convert(radix);

  
  for (unsigned int base = 2; base < (radix-1)*max.size(); base++)
  {
    unsigned int exponent = 1;
    
    BigNum current(base, radix);
    
    while (current < max)
    {
      auto sum = digitSum(current);
      // digit sum equals base ? single-digit numbers excluded
      if (sum == base && current.size() >= 2)
      {
        
        BigNum decimal = current.convert(10);
        solutions.insert(decimal);
      }

      
      current *= base;
      exponent++;
    }
  }

  
  for (auto i : solutions)
  {
    
    for (auto j = i.rbegin(); j != i.rend(); j++)
      std::cout << *j;
    std::cout << " ";
  }

  return 0;
}
#endif
