#include "Student.h"
#include "Course.h"
#include "Registrar.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace BrooklynPoly {
    class Course;
    Student::Student(const string &name) : name(name) {}

    ostream &operator<<(ostream &os, const Student &stu) {
        os << stu.name << ": ";
        vector<Course*> studentCourses = stu.courses;
        if (studentCourses.size() > 0) {
            for (const Course* currCourse : studentCourses) {
                os << currCourse->getName() << " ";
            }
        } else {
            os << "None";
        }
        os << "\n";
        return os;
    }

    string Student::getName() const {
        return name;
    }

    void Student::addCourse(Course* newCourse) {
        courses.push_back(newCourse);
    }

    // delete this later xD
    vector<Course*> Student::getCourses() const {
        return courses;
    }

    void Student::dropCourse(Course* oldCourse) {
        for (Course* currCourse : courses) {
            if (currCourse == oldCourse) {
                swap(courses.back(), currCourse);
                courses.pop_back();
                return;
            }
        }
    }
}
// void swap(vector<Hydrocarbon> &vHydroCarbs, int j) {
//     Hydrocarbon temp = vHydroCarbs[j];
//     vHydroCarbs[j] = vHydroCarbs[j + 1];
//     vHydroCarbs[j + 1] = temp;
// }
