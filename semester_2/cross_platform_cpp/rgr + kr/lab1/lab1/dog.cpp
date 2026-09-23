#include "dog.h"
#include <iostream>

using namespace std;

Dog::Dog() : Animal(), breed("Unknown"), isTrained(false) {
}

Dog::Dog(const string& n, int a, const string& b, bool trained) 
    : Animal(n, a), breed(b), isTrained(trained) {
}

Dog::Dog(const Dog& other)
    : Animal(other), breed(other.breed), isTrained(other.isTrained) {
}

void Dog::makeSound() const {
    cout << name << " says: Woof! Woof!" << endl;
}

string Dog::getType() const {
    return "Dog";
}

void Dog::show() const {
    Animal::show();
    cout << " Type: " << getType() << ", Breed: " << breed << ", Trained: " << (isTrained ? "Yes" : "No");
}

Dog& Dog::operator=(const Dog& other) {
    cout << "Dog operator =" << endl;
    if (this != &other) {
        static_cast<Animal&>(*this) = static_cast<const Animal&>(other);

        breed = other.breed;
        isTrained = other.isTrained;
    }
    return *this;
}

bool Dog::operator==(const Dog& other) const {
    cout << "Dog operator ==" << endl;
    return (static_cast<const Animal&>(*this) == static_cast<const Animal&>(other) && 
        breed == other.breed && 
        isTrained == other.isTrained);
}