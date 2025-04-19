#include <iostream>
#include <vector>
#include <memory>

class Individual {
public:
    virtual void speak() const = 0;
    virtual ~Individual() = default;
};

class Alice : public Individual {
public:
    void speak() const override { std::cout << "Hi, I am Alice" << std::endl; }
};

class Bob : public Individual {
public:
    void speak() const override { std::cout << "Hi, I am Bob" << std::endl; }
};

class Casper : public Individual {
public:
    void speak() const override { std::cout << "Hi, I am Casper" << std::endl; }
};

std::vector<std::unique_ptr<Individual>> createIndividuals() {
    std::vector<std::unique_ptr<Individual>> v;
    for (int i = 0; i < 3; ++i) v.push_back(std::make_unique<Alice>());
    for (int i = 0; i < 2; ++i) v.push_back(std::make_unique<Bob>());
    for (int i = 0; i < 4; ++i) v.push_back(std::make_unique<Casper>());
    return v;
}

void letThemSpeak(const std::vector<std::unique_ptr<Individual>>& v) {
    for (const auto& p : v) p->speak();
}

int main() {
    auto individuals = createIndividuals();
    letThemSpeak(individuals);
    return 0;
}
