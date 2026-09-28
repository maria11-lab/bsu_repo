#include "dog.h"
#include "cat.h"
#include "parrot.h"
#include "shelter.h"

int main() {
    Shelter* mainShelter = new Shelter("Happy Paws");

    mainShelter->add(new Dog("Buddy", 3, "Golden", true));
    mainShelter->add(new Cat("Luna", 2, "Black", true));

    Shelter* birdBlock = new Shelter("Tropical Birds");
    birdBlock->add(new Parrot("Kesha", 1, "Green", true));

    mainShelter->add(birdBlock);

    mainShelter->show();
    cout << endl;

	mainShelter->makeSound();

    delete mainShelter;
    return 0;
}