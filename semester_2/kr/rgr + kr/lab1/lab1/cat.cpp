#include "cat.h"
#include <iostream>
using namespace std;

Cat::Cat() : Animal(), color("Unknown"), isVaccinated(false) {
}

Cat::Cat(const string& n, int a, const string& c, bool v) 
    : Animal(n, a), color(c), isVaccinated(v) {
}

Cat::Cat(const Cat& other) 
    : Animal(other), color(other.color), isVaccinated(other.isVaccinated) {
}

void Cat::makeSound() const {
    cout << name << " says: Meow!" << '\n';
}

string Cat::getType() const {
    return "Cat";
}

void Cat::show() const {
    Animal::show();
    cout << " Type: " << getType() << ", Color: " << color << ", Vaccinated: " << (isVaccinated ? "Yes" : "No");
}

Cat& Cat::operator=(const Cat& other) {
    cout << "Cat operator =" << '\n';
    if (this != &other) {
        static_cast<Animal&>(*this) = static_cast<const Animal&>(other);
        color = other.color;
        isVaccinated = other.isVaccinated;
    }
    return *this;
}

bool Cat::operator==(const Cat& other) const {
    cout << "\nCat operator ==" << '\n';
    return static_cast<const Animal&>(*this) == static_cast<const Animal&>(other) && 
        color == other.color && 
        isVaccinated == other.isVaccinated;
}

ostream& operator<<(ostream& os, const Cat& c) {
    os << static_cast<const Animal&>(c);
    os << " Type: " << c.getType() << ", Color: " << c.color << ", Vaccinated: " << (c.isVaccinated ? "Yes" : "No");
    return os;
}