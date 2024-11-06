#include <iostream>
#include <string>
#include <cctype>

void countLetters(const std::string& str, int& numLetters, int& numDigits)
{
    numLetters = 0;
    numDigits = 0;
    for (std::string::size_type i = 0; i < str.size(); ++i)
    {
        char ch = str[i];
        if (std::isalpha(str[i]))
        {
            ++numLetters;
        }
        else if (std::isdigit(str[i]))
        {
            ++numDigits;
        }
    }
}

int main()
{
    std::string input;
    std::getline(std::cin, input);
    
    int letters = 0;
    int digits = 0;
    
    countLetters(input, letters, digits);

    std::cout << "Количество букв: " << letters << std::endl;
    std::cout << "Количество цифр: " << digits << std::endl;

    return 0;
}