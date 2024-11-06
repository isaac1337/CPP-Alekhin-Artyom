#include <iostream>

std::string repeat(int n)
{
    if (n < 0)
    {
        return "";
    }
    std::string res;
    std::string number = std::to_string(n);
    for(int i = 0; i < n; i++)
    {
        res += number;
    }
    return res;
}

int main()
{
std::cout << repeat(5) << std::endl; // Должно напечатать 55555
std::cout << repeat(10) << std::endl; // Должно напечатать 10101010101010101010
std::cout << repeat(-1) << std::endl; // Не должно ничего печатать
}