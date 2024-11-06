#include <iostream>
#include <string>

bool isDomainName(const std::string& str)
{
    bool startwith = (str.find("www.") == 0);
    bool endwith = (str.size() >= 4 && str.substr(str.size() - 4) == ".com");

    return startwith && endwith;

}

int main()
{
    std::cout << isDomainName("www.google.com") << std::endl; // Напечатает 1 (true)
    std::cout << isDomainName("abc") << std::endl;            // Напечатает 0 (false)
    std::cout << isDomainName("hello.com") << std::endl;      // Напечатает 0 (false)
}