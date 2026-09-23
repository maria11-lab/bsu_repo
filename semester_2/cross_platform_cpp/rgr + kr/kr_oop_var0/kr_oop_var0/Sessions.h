#pragma once
#include "Student.h"
#include <stdexcept>

class Sessions : public Student {
private:
    const size_t maxS_ = 8; 
    size_t realS_;
    double* averageGrades_;

public:
    Sessions() = delete; 

    Sessions(const std::string& lastName, EducationType type, int year, size_t numS);
    ~Sessions();
    
    Sessions(const Sessions& other);
    Sessions& operator=(const Sessions& other);

    Sessions(Sessions&& other) noexcept;
    Sessions& operator=(Sessions&& other) noexcept;

    void setRealSessions(size_t numS);
    void setGrade(size_t index, double grade);
    size_t getMaxSession() const;

    friend std::ostream& operator<<(std::ostream& os, const Sessions& s);
};