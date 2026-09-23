#ifndef SHELTER_H
#define SHELTER_H

#include "animal.h"
#include <vector>
#include <algorithm>

class Shelter : public Animal {
private:
    vector<Animal*> children;

public:
    Shelter(const string& n) : Animal(n, 0) {}

    ~Shelter() {
        for (auto child : children) {
            delete child;
        }
        children.clear();
    }

    void add(Animal* a) override {
        children.push_back(a);
    }

    void remove(Animal* a) override {
        auto it = find(children.begin(), children.end(), a);
        if (it != children.end()) {
            children.erase(it);
        }
    }

    string getType() const override { return "Shelter Group"; }

    void makeSound() const override {
        for (auto child : children) {
            child->makeSound();
        }
    }

    void show() const override {
        cout << "[Shelter ID: " << ID << "] Name: " << name << " {" << endl;
        for (auto child : children) {
            cout << "  ";
            child->show();
            cout << endl;
        }
        cout << "}";
    }
};

#endif