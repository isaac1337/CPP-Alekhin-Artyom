#include <iostream>
#include <string>
#include <vector>

std::string concatenate(const std::vector<std::string>& strings)
{
    std::string result;
    for(size_t i = 0; i < strings.size(); i++)
    {
        const std::string& str = strings[i];
        result += str;
    }
    return result;
}

int main()
{
    std::vector<std::string> v {"Cat", "Dog", "Mouse", "Tiger", "Elk"};
    std::cout << concatenate(v) << std::endl; // Должно напечатать CatDogMouseTigerElk
}