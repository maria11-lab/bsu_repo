# Student Session Management

A C++ console application focused on object-oriented programming and class design.

The project models students and their academic sessions using a class hierarchy and demonstrates core OOP principles through object interaction, inheritance, polymorphism, encapsulation, operator overloading, and resource management.

## OOP Concepts

### Encapsulation

Class data is hidden behind private and protected members and accessed through constructors, getters, setters, and class methods.

### Inheritance

The project uses a multi-level class hierarchy:

Learner
  ↓
Student
  ↓
Sessions

`Student` extends the base `Learner` class, while `Sessions` extends `Student`.

### Polymorphism

The `Learner` class defines a pure virtual `printID()` method, which is implemented by derived classes.

A collection of `Learner*` pointers is used to work with objects of different derived types through a common interface.

### Operator Overloading

The project overloads operators for working with objects:

- `operator==` for comparing students
- `operator<<` for formatted output
- assignment operators

### Copy and Move Semantics

The classes implement:

- copy constructors
- copy assignment operators
- move constructors
- move assignment operators

Move semantics are used when transferring dynamically allocated session data.

### Dynamic Memory Management

The `Sessions` class manages dynamically allocated data.

The implementation includes resource management through constructors, destructors, copy operations, and move operations.

## Functionality

- Create and manage students and academic sessions
- Compare objects
- Store different object types in a common collection
- Count objects by class and education type
- Search students by admission year
- Reorder objects by their class
- Display object information through overloaded output operators
- Demonstrate copy and move operations

## Technologies

- C++
- Object-Oriented Programming (OOP)
- Inheritance
- Polymorphism
- Encapsulation
- Operator Overloading
- Copy and Move Semantics
- Dynamic Memory Management
- STL