#ifndef STUDENT_H
#define STUDENT_H

#include "Course.h"
#include <iostream>
#include <string>
#include <vector>

namespace BrooklynPoly {
    class Course; // Forward decleration

    class Student {
        friend std::ostream &operator<<(std::ostream &os, const Student &stu);
    public:
        Student(const std::string &name);
        std::string getName() const;
        void addCourse(Course*);
        void dropCourse(Course* oldCourse);
    private:
        size_t findCourse(const std::string &courseName);
        std::string name;
        std::vector<Course*> courses;
    };
}

#endif