#ifndef COURSE_H
#define COURSE_H

#include "Registrar.h"
#include "Student.h"
#include <iostream>
#include <string>

namespace BrooklynPoly {
    class Student;
    class Registrar;

    class Course {
        friend std::ostream& operator<<(std::ostream &os, const Course&rhs);
    public:
        Course(const std::string& courseName);
        std::string getName() const;
        void addStudent(Student* newStudent);
        void purge();
    private:
        std::string name;
        std::vector<Student*> students;
    };
}

#endif
