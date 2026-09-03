#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class AnimalType { Dog, Cat, Parrot };

class Animal {
protected:
    static int NextID;          
    const int ID;
    string name;
    int age;
public:
    static int count;
    Animal();
    Animal(const string& n, int a);
    Animal(const Animal& other);
    virtual ~Animal();

    int get_ID() const { return ID; }
    string get_name() const { return name; }
    int get_age() const { return age; }
    void set_name(const string& n) { name = n; }
    void set_age(int a) { age = a; }

    virtual void makeSound() const = 0;
    virtual string getType() const = 0;
    virtual void show() const;

    Animal& operator=(const Animal& other);
    bool operator==(const Animal& other) const;
    friend ostream& operator<<(ostream& os, const Animal& a);

    virtual void add(Animal* a) {};
    virtual void remove(Animal* a) {};
};

#endif