#include <iostream>
#include "Manager.h"

int main() {
    try {
        Student* st1 = new Student("Ivanov", EducationType::FullTime, 2022);
        Student* st2 = new Student("Petrov", EducationType::FullTime, 2022);
        Student* st3 = new Student("Sidorov", EducationType::Evening, 2023);

        std::cout << "Student Comparisons:" << std::endl;
        std::cout << "st1 == st2: " << (*st1 == *st2 ? "True" : "False") << std::endl;
        std::cout << "st1 == st3: " << (*st1 == *st3 ? "True" : "False") << std::endl;

        Sessions* sess_source = new Sessions("Alekseev", EducationType::FullTime, 2021, 3);
        sess_source->setGrade(0, 4.8);

        Sessions* sess_moved = new Sessions(std::move(*sess_source));
        delete sess_source;

        Sessions* sess2 = new Sessions("Pavlov", EducationType::FullTime, 2020, 2);

        std::cout << "\nSessions Comparisons:" << std::endl;
        std::cout << "sess_moved == sess2: " << (*sess_moved == *sess2 ? "True" : "False") << std::endl;

        std::cout << "\nCross-class Comparison:" << std::endl;
        std::cout << "st1 == sess_moved: " << (*st1 == *sess_moved ? "True" : "False") << "\n" << std::endl;

        Manager manager;

        manager.add(st1);
        manager.add(st2);
        manager.add(st3);
        manager.add(sess_moved);
        manager.add(sess2);

        manager.add(new Student("Dmitriev", EducationType::Corres, 2022));
        manager.add(new Sessions("Semenov", EducationType::Distance, 2021, 4));

        manager.printAll();
        std::cout << std::endl;

        manager.countClasses();
        manager.countStats();

        manager.findByYear(2022);
        manager.findByYear(2025);

        manager.transformArray();

        std::cout << "\nResult after transformation:" << std::endl;
        manager.printAll();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}