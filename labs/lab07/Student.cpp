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

    ostream &operator<<(ostream &os, const Student &rhs) {
        os << rhs.name << ": ";
        vector<Course*> studentCourses = rhs.courses;
        if (studentCourses.size() > 0) {
            for (const Course* currCourse : studentCourses) {
                os << currCourse->getName() << " ";
            }
        } else {
            os << "No Courses";
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

    void Student::dropCourse(Course* oldCourse) {
        size_t courseIndex = 0;
        size_t myIndex = 0;
        for (Course* currCourse : courses) {
            if (currCourse == oldCourse) {
                courseIndex = myIndex;
                ++myIndex;
            }
        }
        size_t last = courses.size() - 1;
        for (Course* currCourse : courses) {
            if (currCourse == oldCourse) {
                Course* temp = currCourse;
                courses[courseIndex] = courses[last];
                courses[last] = temp;
                temp = nullptr;
                courses.pop_back();
                return;
            }
        }

    }
}
