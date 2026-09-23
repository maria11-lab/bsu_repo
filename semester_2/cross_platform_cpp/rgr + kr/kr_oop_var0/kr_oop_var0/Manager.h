#pragma once
#include <vector>
#include "Sessions.h"

class Manager {
private:
    std::vector<Learner*> items;

public:
    Manager() = default;
    ~Manager();

    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

    void add(Learner* item);
    void printAll() const;
    void countStats() const;
    void countClasses() const;
    void findByYear(int year) const;
    void transformArray();
};