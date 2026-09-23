#ifndef FACTORIES_H
#define FACTORIES_H

#include "dog.h"
#include "cat.h"
#include "parrot.h"


class AnimalFactory {
public:
    virtual Animal* create(const string& name, int age) = 0;
    virtual ~AnimalFactory() {}
};

class DogFactory : public AnimalFactory {
public:
    Animal* create(const string& name, int age) override {
        return new Dog(name, age, "Unknown", false);
    }
};

class CatFactory : public AnimalFactory {
public:
    Animal* create(const string& name, int age) override {
        return new Cat(name, age, "Unknown", false);  
    }
};

class ParrotFactory : public AnimalFactory {
public:
    Animal* create(const string& name, int age) override {
        return new Parrot(name, age, "hey", false);
    }
};

#endif