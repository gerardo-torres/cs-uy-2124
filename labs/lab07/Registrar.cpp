#include "Student.h"
#include "Course.h"
#include "Registrar.h"
#include <iostream>

using namespace std;

namespace BrooklynPoly {
    ostream& operator<<(std::ostream&os, const Registrar& rhs) {
        vector<Course*> currCourses = rhs.courses;
        vector<Student*> currStudents = rhs.students;
        os << "Registrar's Report\n";
        os << "Courses: \n";
        for (Course* currCourse : currCourses) {
            os << *currCourse << " "; 
        }
        os << "\n";
        os << "Students: \n";
        for (Student* currStudent : currStudents) {
            os << *currStudent << " ";
        }
        os << "\n";
        return os;
    }

    Registrar::Registrar() {
    }
    
    bool Registrar::addCourse(const std::string& courseName) {
        Course* newCourse = new Course(courseName);
        courses.push_back(newCourse);
    }

    bool Registrar::addStudent(const std::string& studentName) {
        Student* newStudent = new Student(studentName);
        students.push_back(newStudent);
    }

    bool Registrar::enrollStudentInCourse(const string& studentName, const std::string &courseName) {
        size_t studentIndex = findStudent(studentName);
        size_t courseIndex = findCourse(courseName);
        if (studentIndex != -1 && courseIndex != -1){
            Student* currStudent = students[studentIndex];
            Course* currCourse = courses[courseIndex];
            currStudent->addCourse(currCourse);
            return true;
        } else {
            std::cerr << "Invalid operation\n";
            return false;
        }
    }

    bool Registrar::cancelCourse(const std::string& courseName) {
        size_t courseIndex = findCourse(courseName);
        Course* oldCourse = courses[courseIndex];
        for (Student* student: students){
            student->dropCourse(oldCourse);
        }
        oldCourse->purge();
        swap(courses.back(), courses[courseIndex]);
        courses.pop_back();
        delete courses[courses.size()];
    }

    void Registrar::purge() {
        for (Student* currStudent : students) {
            delete currStudent;
        }
        students.clear();
        for (Course* currCourse : courses) {
            delete currCourse;
        }
        courses.clear();
    }

    size_t Registrar::findStudent(const std::string &studentName) {
        size_t index = 0;
        for (Student* currStudent : students) {
            std::string currName = currStudent->getName();
            if (currName == studentName) {
                return index;
            }
            index++;
        }
        return -1;  // Student not found; return -1
    }

    size_t Registrar::findCourse(const std::string &courseName) {
        size_t index = 0;
        for (Course* currCourse : courses) {
            std::string currName = currCourse->getName();
            if (currName == courseName) {
                return index;
            }
            index++;
        }
        return -1;  // Course not found; return -1
    }

}