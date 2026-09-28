#ifndef KSETITER_H
#define KSETITER_H

#include "KSet.h"

class KSetIter {
    const KSet& set;
    int index;

public:
    KSetIter(const KSet& s) : set(s), index(0) {}

    void first() { index = 0; }
    void next() { index++; }
    bool isDone() const { return index >= set.count; }
    int currentItem() const { return set.items[index]; }

    void operator++() { index++; }
    bool operator()() { return index < set.count; }
    int operator*() { return set.items[index]; }
};

inline KSetIter* KSet::createIterator() const {
    return new KSetIter(*this);
}

#endif