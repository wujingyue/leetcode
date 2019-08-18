#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class Solution {
 public:
  std::string numberToWords(int num) {
    if (num == 0) {
      return "Zero";
    }

    int billions = num / 1000 / 1000 / 1000;
    int millions = num / 1000 / 1000 % 1000;
    int thousands = num / 1000 % 1000;
    int ones = num % 1000;

    std::vector<std::string> words;
    if (billions > 0) {
      Read(billions, &words);
      words.push_back("Billion");
    }
    if (millions > 0) {
      Read(millions, &words);
      words.push_back("Million");
    }
    if (thousands > 0) {
      Read(thousands, &words);
      words.push_back("Thousand");
    }
    if (ones > 0) {
      Read(ones, &words);
    }

    std::string result;
    for (size_t i = 0; i < words.size(); ++i) {
      if (i > 0) {
        result += ' ';
      }
      result += words[i];
    }
    return result;
  }

 private:
  void ReadDigit(int digit, std::vector<std::string>* words) {
    assert(digit >= 1 && digit <= 9);
    switch (digit) {
      case 1: words->push_back("One"); break;
      case 2: words->push_back("Two"); break;
      case 3: words->push_back("Three"); break;
      case 4: words->push_back("Four"); break;
      case 5: words->push_back("Five"); break;
      case 6: words->push_back("Six"); break;
      case 7: words->push_back("Seven"); break;
      case 8: words->push_back("Eight"); break;
      case 9: words->push_back("Nine"); break;
      default: break;
    }
  }

  void ReadTens(int digit, std::vector<std::string>* words) {
    assert(digit >= 1 && digit <= 9);
    switch (digit) {
      case 1: words->push_back("Ten"); break;
      case 2: words->push_back("Twenty"); break;
      case 3: words->push_back("Thirty"); break;
      case 4: words->push_back("Forty"); break;
      case 5: words->push_back("Fifty"); break;
      case 6: words->push_back("Sixty"); break;
      case 7: words->push_back("Seventy"); break;
      case 8: words->push_back("Eighty"); break;
      case 9: words->push_back("Ninety"); break;
      default: break;
    }
  }

  void Read(int num, std::vector<std::string>* words) {
    int hundreds = num / 100;
    int tens = num / 10 % 10;
    int ones = num % 10;
    if (hundreds > 0) {
      ReadDigit(hundreds, words);
      words->push_back("Hundred");
    }
    if (tens >= 2) {
      ReadTens(tens, words);
      if (ones > 0) {
        ReadDigit(ones, words);
      }
    } else if (tens == 0) {
      if (ones > 0) {
        ReadDigit(ones, words);
      }
    } else {
      assert(tens == 1);
      switch (ones) {
        case 0: words->push_back("Ten"); break;
        case 1: words->push_back("Eleven"); break;
        case 2: words->push_back("Twelve"); break;
        case 3: words->push_back("Thirteen"); break;
        case 4: words->push_back("Fourteen"); break;
        case 5: words->push_back("Fifteen"); break;
        case 6: words->push_back("Sixteen"); break;
        case 7: words->push_back("Seventeen"); break;
        case 8: words->push_back("Eighteen"); break;
        case 9: words->push_back("Nineteen"); break;
        default: break;
      }
    }
  }
};

int main() {
  Solution solution;
  std::cout << solution.numberToWords(123) << std::endl;
  std::cout << solution.numberToWords(12345) << std::endl;
  std::cout << solution.numberToWords(1234567) << std::endl;
  std::cout << solution.numberToWords(1234567891) << std::endl;
}
