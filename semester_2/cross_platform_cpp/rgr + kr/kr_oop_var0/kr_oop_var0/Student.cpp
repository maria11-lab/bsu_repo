#include "Student.h"

Student::Student(const std::string& lastName, EducationType type, int year) 
    : lastName_(lastName), type_(type), admissionYear_(year) {}

Student::Student(const Student& other) 
    : Learner(), lastName_(other.lastName_), type_(other.type_), admissionYear_(other.admissionYear_) {}

Student& Student::operator=(const Student& other) {
    if (this == &other) return *this;
    type_ = other.type_;
    lastName_ = other.lastName_;
    return *this;
}

Student::Student(Student&& other) noexcept 
    : Learner(), lastName_(std::move(other.lastName_)),
    type_(other.type_), admissionYear_(other.admissionYear_) {}

Student& Student::operator=(Student&& other) noexcept {
    if (this == &other) return *this;
    lastName_ = std::move(other.lastName_);
    type_ = other.type_;

    return *this;
}

bool Student::operator==(const Student& other) const {
    return this->type_ == other.type_;
}

void Student::printID(std::ostream& os) const { os << id; }

void Student::setLastName(const std::string& lastName) { lastName_ = lastName; }
void Student::setType(EducationType type) { type_ = type; }

std::string Student::getLastName() const { return lastName_; }
int Student::getYear() const { return admissionYear_; }
EducationType Student::getType() const { return type_; }

std::ostream& operator<<(std::ostream& os, const Student& s) {
    s.printID(os);
    os << " | Name: " << s.lastName_ << " | Year: " << s.admissionYear_ << " | Type: ";
    switch (s.type_) {
    case EducationType::FullTime: os << "Full-time"; break;
    case EducationType::Evening: os << "Evening"; break;
    case EducationType::Corres: os << "Correspondence"; break;
    case EducationType::Distance: os << "Distance"; break;
    }
    return os;
}