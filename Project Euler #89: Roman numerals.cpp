//Language: C++
//by Rahul Balamwar

#include <iostream>
#include <string>

// convert valid roman numbers to binary numbers
unsigned int roman2number(const std::string& roman)
{
  unsigned int result = 0;

  // remember the value of the previous Roman letter
  unsigned int last = 0;
  // true, if the current letter is subtracted (and the next identical letters)
  bool subtract = false;

  // walk through the whole string from the end to the beginning ...
  for (auto i = roman.rbegin(); i != roman.rend(); i++)
  {
    unsigned int current = 0;
    switch (*i)
    {
    case 'M': current = 1000; break;
    case 'D': current =  500; break;
    case 'C': current =  100; break;
    case 'L': current =   50; break;
    case 'X': current =   10; break;
    case 'V': current =    5; break;
    case 'I': current =    1; break;
    }

    // smaller than its right neighbor ? => we must subtract
    if (current < last)
    {
      subtract = true;
      last = current;
    }
    // bigger than its right neighbor ? => we must add
    else if (current > last)
    {
      subtract = false;
      last = current;
    }

    // note: if current == last then we keep the variables "subtract" and "last" in their current state

    // add/subtract accordingly
    if (subtract)
      result -= current;
    else
      result += current;
  }

  return result;
}

std::string number2roman(unsigned int number)
{
  // apply these rules in the presented order:
  // - as long as number >= steps[i] add roman[i] to result
  const unsigned int NumRules = 13;
  const unsigned int rules[NumRules] =
    { 1000,  900, 500,  400, 100,  90,   50,   40,  10,    9,   5,    4,  1  };
  const char* action[NumRules] =
    {  "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

  // apply all rules ...
  std::string result;
  for (unsigned int i = 0; i < NumRules; i++)
    // ... as often as needed
    while (number >= rules[i])
    {
      // reduce integer
      number -= rules[i];
      // add letter(s)
      result += action[i];
    }

  return result;
}

int main()
{
  // letters saved by optimization
  unsigned int saved = 0;

  unsigned int tests = 1000;
//#define ORIGINAL
#ifndef ORIGINAL
  std::cin >> tests;
#endif

  while (tests--)
  {
    // read Roman number
    std::string roman;
    std::cin >> roman;

    // convert it to an integer and back to an optimal Roman number
    auto number    = roman2number(roman);
    auto optimized = number2roman(number);

    // count how many character were saved
    saved += roman.size() - optimized.size();

#ifndef ORIGINAL
    // print Roman number
    std::cout << optimized << std::endl;
#endif
  }

#ifdef ORIGINAL
  std::cout << saved << std::endl;
#endif
  return 0;
}
