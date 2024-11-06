#include <iostream>
#include <vector>

void print(const std::vector<int>& v)
{
    for (std::size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

void doubling(std::vector<int>& v)
{
        v.insert(v.end(), v.begin(), v.end());
}

int main()
{
    std::vector<int> v {10, 20, 30};
    doubling(v);
    print(v); // Должно напечатать 10 20 30 10 20 30
}
