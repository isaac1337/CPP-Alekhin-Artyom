#include <iostream>
#include <string>

struct Book
{
    std::string title;
    int pages;
    float price;
};

bool is_expensive(const Book& a)
{
    return a.price > 1000; 
}

int main()
{
    Book book1 = {"Математический анализ Петрович", 300, 5000000.50};
    Book book2 = {"Математический анализ Иванов", 200, 5.80};
    std::cout << "Эта книга " << book1.title << " дорогая: " << std::boolalpha << is_expensive(book1) << std::endl;
    std::cout << "Эта книга " << book2.title << " дорогая: " << std::boolalpha << is_expensive(book2) << std::endl;
}