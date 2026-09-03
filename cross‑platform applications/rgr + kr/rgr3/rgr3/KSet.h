#ifndef KSET_H
#define KSET_H

#include <iostream>
#include <algorithm>

class KSetIter;

class KSet {
    int* items;
    int capacity;
    int count;

public:
    friend class KSetIter;

    KSet(int cap = 100) : capacity(cap), count(0) {
        items = new int[capacity];
    }

    KSet(const KSet& other) : capacity(other.capacity), count(other.count) {
        items = new int[capacity];
        for (int i = 0; i < count; i++) items[i] = other.items[i];
    }

    ~KSet() { 
        delete[] items; 
    }

    int Size() const { return count; }
    bool IsEmpty() const { return count == 0; }
    bool IsFull() const { return count == capacity; }
    void Clear() { count = 0; }

    bool Contains(int val) const {
        for (int i = 0; i < count; i++) {
            if (items[i] == val) return true;
        }
        return false;
    }

    KSet& operator=(const KSet& other) {
        if (this != &other) {
            delete[] items;
            capacity = other.capacity;
            count = other.count;
            items = new int[capacity];
            for (int i = 0; i < count; i++) items[i] = other.items[i];
        }
        return *this;
    }

    KSet& operator>>(int val) {
        if (!Contains(val) && !IsFull()) items[count++] = val;
        return *this;
    }

    KSet operator|(const KSet& other) const {
        KSet res(capacity + other.capacity);
        for (int i = 0; i < count; i++) res >> items[i];
        for (int i = 0; i < other.count; i++) res >> other.items[i];
        return res;
    }

    KSet operator&(const KSet& other) const {
        KSet res(std::min(capacity, other.capacity));
        for (int i = 0; i < count; i++) {
            if (other.Contains(items[i])) res >> items[i];
        }
        return res;
    }

    KSet operator/(const KSet& other) const {
        KSet res(capacity);
        for (int i = 0; i < count; i++) {
            if (!other.Contains(items[i])) res >> items[i];
        }
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const KSet& s) {
        os << "{ ";
        for (int i = 0; i < s.count; i++) os << s.items[i] << " ";
        os << "}";
        return os;
    }

    KSetIter* createIterator() const;
};

#endif