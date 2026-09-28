#ifndef PARROT_H
#define PARROT_H

#include "animal.h"

class Parrot : public Animal {
private:
    string vocabulary;
    bool canFly;

public:
    Parrot();
    Parrot(const string& n, int a, const string& v, bool fly);
    Parrot(const Parrot& other);

    string getVocabulary() const { return vocabulary; }
    bool getCanFly() const { return canFly; }

    void setVocabulary(const string& v) { vocabulary = v; }
    void setCanFly(bool f) { canFly = f; }

    void makeSound() const override;
    string getType() const override;
    void show() const override;

    Parrot& operator=(const Parrot& other);
    bool operator==(const Parrot& other) const;

    friend ostream& operator<<(ostream& os, const Parrot& p);
};

#endif