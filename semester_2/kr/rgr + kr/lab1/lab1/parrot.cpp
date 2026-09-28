#include "parrot.h"
#include <iostream>
using namespace std;

Parrot::Parrot() : Animal(), vocabulary("None"), canFly(true) {
}

Parrot::Parrot(const string& n, int a, const string& v, bool fly) 
    : Animal(n, a), vocabulary(v), canFly(fly) {
}

Parrot::Parrot(const Parrot& other) 
    : Animal(other), vocabulary(other.vocabulary), canFly(other.canFly) {
}

void Parrot::makeSound() const {
    cout << name << " says: " << vocabulary << "!\n";
}

string Parrot::getType() const {
    return "Parrot";
}

void Parrot::show() const {
    Animal::show();
    cout << " Type: " << getType() << ", Vocabulary: \"" << vocabulary << "\", Can fly: " << (canFly ? "Yes" : "No");
}

Parrot& Parrot::operator=(const Parrot& other) {
    cout << "Parrot operator =" << '\n';
    if (this != &other) {
        static_cast<Animal&>(*this) = static_cast<const Animal&>(other);
        vocabulary = other.vocabulary;
        canFly = other.canFly;
    }
    return *this;
}

bool Parrot::operator==(const Parrot& other) const {
    cout << "\nParrot operator ==" << '\n';
    return static_cast<const Animal&>(*this) == static_cast<const Animal&>(other) && 
        vocabulary == other.vocabulary && 
        canFly == other.canFly;
}

ostream& operator<<(ostream& os, const Parrot& p) {
    os << static_cast<const Animal&>(p);
    os << " Type: " << p.getType() << ", Vocabulary: \"" << p.vocabulary << "\", Can fly: " << (p.canFly ? "Yes" : "No");
    return os;
}