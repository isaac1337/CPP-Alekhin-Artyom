#include <iostream>
#include <vector>
#include <typeinfo>

class Individual {
public:
    virtual void speak() const = 0;
    virtual int id() const = 0;
    virtual ~Individual() = default;
};

class Alice : public Individual {
public:
    void speak() const override { std::cout << "Hi, I am Alice" << std::endl; }
    int id() const override { return 0; }
};

class Bob : public Individual {
public:
    void speak() const override { std::cout << "Hi, I am Bob" << std::endl; }
    int id() const override { return 1; }
};

class Casper : public Individual {
public:
    void speak() const override { std::cout << "Hi, I am Casper" << std::endl; }
    int id() const override { return 2; }
};

std::vector<Individual*> createIndividuals() {
    std::vector<Individual*> v;
    for (int i = 0; i < 3; ++i) v.push_back(new Alice);
    for (int i = 0; i < 2; ++i) v.push_back(new Bob);
    for (int i = 0; i < 4; ++i) v.push_back(new Casper);
    return v;
}

void letThemSpeak(const std::vector<Individual*>& v) {
    for (auto p : v) p->speak();
}

void deleteIndividuals(const std::vector<Individual*>& v) {
    for (auto p : v) delete p;
}

int identificationVirtual(Individual* p) {
    return p->id();
}

int identificationDynamic(Individual* p) {
    if (dynamic_cast<Alice*>(p)) return 0;
    if (dynamic_cast<Bob*>(p)) return 1;
    if (dynamic_cast<Casper*>(p)) return 2;
    return -1;
}

int identificationTypeId(Individual* p) {
    if (typeid(*p) == typeid(Alice)) return 0;
    if (typeid(*p) == typeid(Bob)) return 1;
    if (typeid(*p) == typeid(Casper)) return 2;
    return -1;
}

int main() {
    auto v = createIndividuals();
    letThemSpeak(v);
    for (auto p : v) std::cout << identificationVirtual(p) << std::endl;
    for (auto p : v) std::cout << identificationDynamic(p) << std::endl;
    for (auto p : v) std::cout << identificationTypeId(p) << std::endl;
    deleteIndividuals(v);
    return 0;
}
