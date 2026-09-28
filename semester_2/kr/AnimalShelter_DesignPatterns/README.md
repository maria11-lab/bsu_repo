# Animal Shelter — Design Patterns

A C++ project developed as a set of laboratory works on object-oriented design patterns.

The project implements an animal shelter system and demonstrates the use of the
Factory Method and Composite design patterns.

## Description

The project is based on an object-oriented hierarchy of animals.
The base `Animal` class is extended by several concrete animal types:

- `Dog`
- `Cat`
- `Parrot`

Each animal has its own characteristics and implements common operations such as
displaying information and making sounds.

The project was developed incrementally as part of three laboratory works.

## Design Patterns

### Factory Method

The Factory Method pattern is used to create different types of animals.

The project contains:

- `AnimalFactory` — base factory interface;
- `DogFactory` — creates `Dog` objects;
- `CatFactory` — creates `Cat` objects;
- `ParrotFactory` — creates `Parrot` objects.

This separates object creation from the code that uses the created objects.

### Composite

The Composite pattern is used to represent groups of animals.

The `Shelter` class can contain different `Animal` objects, including other
`Shelter` objects. This allows individual animals and groups of animals to be
handled through the common `Animal` interface.

## Features

- Animal class hierarchy
- `Dog`, `Cat`, and `Parrot` implementations
- Factory Method for animal creation
- Composite structure for animal groups
- Polymorphic `makeSound()` and `show()` operations
- Object copying and assignment operators
- Animal comparison
- Automatic object ID generation

## Technologies

- C++
- Object-Oriented Programming
- Inheritance
- Polymorphism
- Factory Method
- Composite
- STL 