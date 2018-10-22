#include "Student.h"
#include "Course.h"
#include "Registrar.h"
#include <iostream>
#include <vector>
#include <string>

namespace BrooklynPoly {
    Course::Course(const std::string& courseName) 
    : name(courseName) {}

    std::ostream &operator<<(std::ostream& os, const Course& rhs) {
        os << rhs.name << ": ";
        if (rhs.students.size() > 0) {
            for (const Student* currStudent : rhs.students)  {
                os << currStudent->getName() << " ";
            }
        } else {
            os << "No Students";
        }
        os << "\n";
        return os;
    }

    std::string Course::getName() const {
        return name;
    }

    void Course::addStudent(Student* newStudent) {
        students.push_back(newStudent);
    }

    void Course::purge() {
        students.clear();
    }
}
