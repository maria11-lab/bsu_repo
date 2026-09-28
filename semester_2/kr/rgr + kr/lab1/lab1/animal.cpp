#include "animal.h"
#include <iostream>

using namespace std;

int Animal::NextID = 1;
int Animal::count = 0;

Animal::Animal() : ID(NextID++), name("Unknown"), age(0) {
    count++;
}

Animal::Animal(const string& n, int a) : ID(NextID++), name(n), age(a) {
    count++;
}

Animal::Animal(const Animal& other) : ID(NextID++), name(other.name), age(other.age) {
    count++;
}

Animal::~Animal() {
    count--;
}

void Animal::show() const {
    cout << "ID: " << ID << ", Name: " << name << ", Age: " << age;
}

Animal& Animal::operator=(const Animal& other) {
    if (this != &other) {
        name = other.name;
        age = other.age;
    }
    return *this;
}

bool Animal::operator==(const Animal& other) const {
    return (name == other.name && age == other.age);
}

ostream& operator<<(ostream& os, const Animal& a) {
    os << "ID: " << a.ID << ", Name: " << a.name << ", Age: " << a.age;
    return os;
}