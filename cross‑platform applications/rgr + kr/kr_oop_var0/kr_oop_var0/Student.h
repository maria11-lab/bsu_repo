#pragma once
#include "Learner.h"

enum class EducationType { FullTime, Evening, Corres, Distance };

class Student : public Learner {
protected:
    std::string lastName_;
    EducationType type_;
    const int admissionYear_;

public:
    Student() = delete;
    Student(const std::string& lastName, EducationType type, int year);

    Student(const Student& other);
    Student& operator=(const Student& other);

    Student(Student&& other) noexcept;
    Student& operator=(Student&& other) noexcept;

    bool operator==(const Student& other) const;

    void printID(std::ostream& os) const override;

    void setLastName(const std::string& lastName);
    void setType(EducationType type);

    std::string getLastName() const;
    int getYear() const;
    EducationType getType() const;

    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};