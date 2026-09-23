#ifndef CAT_H
#define CAT_H

#include "animal.h"

class Cat : public Animal {
private:
    string color;
    bool isVaccinated;

public:
    Cat();
    Cat(const string& n, int a, const string& c, bool v);
    Cat(const Cat& other);

    string getColor() const { return color; }
    bool getVaccinated() const { return isVaccinated; }

    void setColor(const string& c) { color = c; }
    void setVaccinated(bool v) { isVaccinated = v; }

    void makeSound() const override;
    string getType() const override;
    void show() const override;

    Cat& operator=(const Cat& other);
    bool operator==(const Cat& other) const;

    friend ostream& operator<<(ostream& os, const Cat& c);
};

#endif