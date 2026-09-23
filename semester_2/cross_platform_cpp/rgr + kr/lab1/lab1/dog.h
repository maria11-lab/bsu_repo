#ifndef DOG_H
#define DOG_H

#include "animal.h"

class Dog : public Animal {
private:
    string breed;
    bool isTrained;

public:
    Dog();
    Dog(const string& n, int a, const string& b, bool trained);
    Dog(const Dog& other);

    string getBreed() const { return breed; }
    bool getTrained() const { return isTrained; }

    void setBreed(const string& b) { breed = b; }
    void setTrained(bool t) { isTrained = t; }

    void makeSound() const override;
    string getType() const override;
    void show() const override;

    Dog& operator=(const Dog& other);
    bool operator==(const Dog& other) const;

    friend ostream& operator<<(ostream& os, const Dog& d);
};

#endif