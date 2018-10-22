#include "Student.h"
#include "Course.h"
#include "Registrar.h"
#include <iostream>

using namespace std;

namespace BrooklynPoly {
    ostream& operator<<(std::ostream&os, const Registrar& rhs) {
        vector<Course*> rhsCourses = rhs.courses;
        vector<Student*> rhsStudents = rhs.students;
        os << "Registrar's Report\nCourses:\n";
        for (Course* currCourse : rhsCourses) {
            os << *currCourse;
        }
        os << "Students:\n";
        for (Student* currStudent : rhsStudents) {
            os << *currStudent << " ";
        }
        return os;
    }

    Registrar::Registrar() {}
    
    bool Registrar::addCourse(const std::string& courseName) {
        size_t courseIndex = findCourse(courseName);
        if (courseIndex == -1) {
            Course* newCourse = new Course(courseName);
            courses.push_back(newCourse);
            return true;
        }
        return false;
    }

    bool Registrar::addStudent(const std::string& studentName) {
        size_t studentIndex = findStudent(studentName);
        if (studentIndex == -1) {
            Student* newStudent = new Student(studentName);
            students.push_back(newStudent);
            return true;
        }
        return false;
    }

    bool Registrar::enrollStudentInCourse(const string& studentName, 
                                     const std::string& courseName) {
        size_t studentIndex = findStudent(studentName);
        size_t courseIndex = findCourse(courseName);
        if (studentIndex != -1 && courseIndex != -1) {
            Student* currStudent = students[studentIndex];
            Course* currCourse = courses[courseIndex];
            currStudent->addCourse(currCourse);
            currCourse->addStudent(currStudent);
            return true;
        }
        return false;
    }

    bool Registrar::cancelCourse(const std::string& courseName) {
        size_t courseIndex = findCourse(courseName);
        if (courseIndex != -1) {
            Course* oldCourse = courses[courseIndex];
            for (Student* currStudent : students) {
                currStudent->dropCourse(oldCourse);
            }
            size_t last = courses.size() - 1;
            oldCourse->purge();
            Course* temp = oldCourse;
            courses[courseIndex] = courses[last];
            courses[last] = temp;
            courses.pop_back();
            return true;
        }
        return false;
    }

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void Registrar::purge() {
        for (Student* currStudent : students) {
            delete currStudent;
        }
        for (Course* currCourse : courses) {
            delete currCourse;
        }
        students.clear();
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