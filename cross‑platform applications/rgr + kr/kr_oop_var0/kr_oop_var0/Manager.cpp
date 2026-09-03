#include "Manager.h"
#include <algorithm>

Manager::~Manager() {
    for (auto item : items) {
        delete item;
    }
    items.clear();
}

void Manager::add(Learner* item) {
    if (item) items.push_back(item);
}

void Manager::printAll() const {
    std::cout << "Learner List:" << std::endl;
    for (const auto& item : items) {
        if (auto* s = dynamic_cast<Sessions*>(item)) std::cout << *s << " (Class: Sessions)" << std::endl;
        else if (auto* st = dynamic_cast<Student*>(item)) std::cout << *st << " (Class: Student)" << std::endl;
    }
}

void Manager::countClasses() const {
    int stCount = 0, sessCount = 0;
    for (auto item : items) {
        if (dynamic_cast<Sessions*>(item)) sessCount++;
        else if (dynamic_cast<Student*>(item)) stCount++;
    }
    std::cout << "Students: " << stCount << " | Sessions: " << sessCount << std::endl;
}

void Manager::countStats() const {
    int ft = 0, ev = 0, cr = 0, ds = 0;
    for (auto item : items) {
        if (auto* s = dynamic_cast<Student*>(item)) {
            EducationType t = s->getType();
            if (t == EducationType::FullTime) ft++;
            else if (t == EducationType::Evening) ev++;
            else if (t == EducationType::Corres) cr++;
            else if (t == EducationType::Distance) ds++;
        }
    }
    std::cout << "Stats - Full-time: " << ft << ", Evening: " << ev << ", Correspondence: " << cr << ", Distance: " << ds << std::endl;
}

void Manager::findByYear(int year) const {
    std::cout << "\nSearching for students admitted in " << year << ":" << std::endl;
    bool found = false;
    for (auto item : items) {
        if (auto* s = dynamic_cast<Student*>(item)) {
            if (s->getYear() == year) {
                std::cout << *s << std::endl;
                found = true;
            }
        }
    }
    if (!found) std::cout << "No records found for " << year << "." << std::endl;
}

void Manager::transformArray() {
    std::vector<Learner*> sessions;
    std::vector<Learner*> students;

    for (auto item : items) {
        if (dynamic_cast<Sessions*>(item)) sessions.push_back(item);
        else students.push_back(item);
    }

    if (sessions.empty() || students.empty()) {
        std::cout << "\nTransformation impossible: missing one of the classes." << std::endl;
        return;
    }

    std::vector<Learner*> result;
    size_t i = 0, j = 0;
    int movedCount = 0;

    while (i < sessions.size() && j < students.size()) {
        result.push_back(sessions[i++]);
        result.push_back(students[j++]);
    }
    while (i < sessions.size()) result.push_back(sessions[i++]);
    while (j < students.size()) result.push_back(students[j++]);

    for (size_t k = 0; k < items.size(); ++k) {
        if (items[k] != result[k]) movedCount++;
    }

    items = std::move(result);
    if (movedCount == 0) std::cout << "\nArray was already ordered correctly." << std::endl;
    else std::cout << "\nArray transformed. Objects moved: " << movedCount << std::endl;
}