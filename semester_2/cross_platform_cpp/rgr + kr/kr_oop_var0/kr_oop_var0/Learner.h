#pragma once
#include <iostream>
#include <string>

class Learner {
protected:
    static size_t NEXT_ID;
    const size_t id;

public:
    Learner();
    virtual ~Learner();

    virtual void printID(std::ostream& os) const = 0;
    size_t getId() const;
};