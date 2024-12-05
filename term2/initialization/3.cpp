#include <iostream>
#include <string>
#include <vector>

int main() {
    int* intObj = new int(123);

    std::string* stringObj = new std::string("Cats and Dogs");

    int* intArray = new int[5]{10, 20, 30, 40, 50};

    std::vector<int>* vectorObj = new std::vector<int>({10, 20, 30, 40, 50});

    std::string* stringArray = new std::string[3]{"Cat", "Dog", "Mouse"};

    std::cout << "intObj: " << *intObj << std::endl;
    std::cout << "stringObj: " << *stringObj << std::endl;

    std::cout << "intArray: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << intArray[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "vectorObj: ";
    for (const int& elem : *vectorObj) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::cout << "stringArray: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << stringArray[i] << " ";
    }
    std::cout << std::endl;

    delete intObj;
    delete stringObj;
    delete[] intArray;
    delete vectorObj;
    delete[] stringArray;

    return 0;
}
