#ifndef REGISTRAR_H
#define REGISTRAR_H

#include "Course.h"
#include "Student.h"
#include <iostream>
#include <string>
#include <vector>

namespace BrooklynPoly  {
    class Student;
    class Course;

    class Registrar {
        friend std::ostream &operator<<(std::ostream& os, const Registrar& rhs);
    public:
        Registrar();
        void display();
        bool addCourse(const std::string &courseName);
        bool addStudent(const std::string &studentName);
        bool enrollStudentInCourse(const std::string &studentName,
                                const std::string &courseName);
        bool cancelCourse(const std::string &courseName);
        void purge();
    private:
        size_t findStudent(const std::string &studentName);
        size_t findCourse(const std::string &courseName);
        std::vector<Course*> courses;
        std::vector<Student*> students;
    };
}

#endif