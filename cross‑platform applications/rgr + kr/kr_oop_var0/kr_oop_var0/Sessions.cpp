#include "Sessions.h"

Sessions::Sessions(const std::string& LastName, EducationType type, int year, size_t numS) 
    : Student(LastName, type, year) {
    if (numS > maxS_) {
        throw std::runtime_error("Exceeded maximum number of sessions");
    }
    realS_ = numS;
    averageGrades_ = new double[realS_];
    for (size_t i = 0; i < realS_; ++i) averageGrades_[i] = 0.0;
}

Sessions::~Sessions() {
    delete[] averageGrades_;
}

Sessions::Sessions(const Sessions& other) : Student(other), realS_(other.realS_) {
    averageGrades_ = new double[realS_];
    for (size_t i = 0; i < realS_; ++i) {
        averageGrades_[i] = other.averageGrades_[i];
    }
}

Sessions& Sessions::operator=(const Sessions& other) {
    if (this == &other) return *this;
    Student::operator=(other);

    delete[] averageGrades_;
    realS_ = other.realS_;
    averageGrades_ = new double[realS_];
    for (size_t i = 0; i < realS_; ++i) {
        averageGrades_[i] = other.averageGrades_[i];
    }
    return *this;
}


Sessions::Sessions(Sessions&& other) noexcept 
    : Student(std::move(other)), realS_(other.realS_), averageGrades_(other.averageGrades_) {
    other.averageGrades_ = nullptr;
    other.realS_ = 0;
}
Sessions& Sessions::operator=(Sessions&& other) noexcept {
    if (this == &other) return *this;
    Student::operator=(std::move(other));

    delete[] averageGrades_;
    averageGrades_ = other.averageGrades_;
    realS_ = other.realS_;

    other.averageGrades_ = nullptr;
    other.realS_ = 0;
    return *this;
}

void Sessions::setRealSessions(size_t numS) {
    if (numS > maxS_) {
        throw std::runtime_error("Exceeded maximum number of sessions");
    }

    double* newGrades = new double[numS];
    for(size_t i = 0; i < (numS < realS_ ? numS : realS_); ++i) 
        newGrades[i] = averageGrades_[i];

    delete[] averageGrades_;
    averageGrades_ = newGrades;
    realS_ = numS;
}
void Sessions::setGrade(size_t index, double grade) {
    if (index >= 0 && index < realS_) {
        averageGrades_[index] = grade;
    } else {
        throw std::out_of_range("Index out of bounds for grades");
    }
}

size_t Sessions::getMaxSession() const { return maxS_; }

std::ostream& operator<<(std::ostream& os, const Sessions& s) {
    os << static_cast<const Student&>(s); 

    os << " | Sessions: " << s.realS_ << "/" << s.maxS_;
    if (s.realS_ > 0) {
        os << " | Grades: [ ";
        for (size_t i = 0; i < s.realS_; ++i) {
            os << s.averageGrades_[i];
			if (i < s.realS_ - 1) os << "; ";
        }
        os << "]";
    } else {
        os << " | No sessions completed yet";
    }
    return os;
}