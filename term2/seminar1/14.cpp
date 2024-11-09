#include <iostream>
#include <string>
#include <vector>

void print(const std::vector<std::size_t>& v)
{
    for (std::size_t i = 0; i < v.size(); ++i)
    std::cout << v[i] << " ";
    std::cout << std::endl;
}
// Тут нужно написать функцию substringIndexes

std::vector<std::size_t> substringIndexes(const std::string& str, const std::string& substr)
{
    std::vector<std::size_t> indexes;
    std::size_t pos = str.find(substr, 0);
    while (pos != std::string::npos)    
    {
        indexes.push_back(pos);
        pos = str.find(substr, pos + 1);
    }

    return indexes;
}
int main()
{
    std::vector<std::size_t> v1 = substringIndexes("cat and dog and cat", "cat");
    print(v1); // Должно напечатать 0 16
    std::vector<std::size_t> v2 = substringIndexes("look, cats were here", "cat");
    print(v2); // Должно напечатать 6
    std::vector<std::size_t> v3 = substringIndexes("catcatcatcatcatcat", "cat");
    print(v3); // Должно напечатать 0 3 6 9 12 15
    std::vector<std::size_t> v4 = substringIndexes("dog mouse elephant", "cat");
    print(v4); // Не должно ничего печатать
}