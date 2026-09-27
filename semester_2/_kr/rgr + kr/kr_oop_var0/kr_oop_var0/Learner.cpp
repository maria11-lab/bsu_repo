#include "Learner.h"

size_t Learner::NEXT_ID = 1;

Learner::Learner() : id(NEXT_ID++) {}

Learner::~Learner() {}

size_t Learner::getId() const {
    return id;
}