/*
Author:         Gerardo Torres
Class:          CS-UY 2124
File Name:      rec05.cpp
-----------------------------------------------------------
Description:    Modeling the School of Engineering CS lab
                administration
-----------------------------------------------------------
compile:        $ g++ rec05.cpp -o rec05
run:            $ ./rec05
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class LabWorker; // forward decleration

class Section {
    // the container for student lab records

    class TimeSlot {
        // the day of the week and the hour (24HR) the lab begins
    public:
        TimeSlot(const string& day, int hour) 
        : day(day), hour(hour) { }

        string getDay() const {
            return day;
        }

        int getHour() const {
            return hour;
        }

        string getFormattedHour() const {
            if (hour > 12) {
                return to_string(hour - 12) + "PM";
            } else if (hour == 12) {
                return "12PM";
            }
            return to_string(hour) + "AM";
        }

    private:
        string day;
        int hour;
    };

    class Student {
        // the student record; contains their name and their grades
    public:
        Student(const string& name) : name(name), grades(14, -1){}
        
        string getName() const {
            return name;
        }

        vector<int> getGrades() const {
            return grades;
        }

        void addGrade(int week, int grade) {
            grades[week - 1] = grade;
        }

    private:
        string name;
        vector<int> grades;
    };

public:
    // default constructor
    Section(const string& name, const string& day, int hour) 
    : name(name), vacant(true), slot(TimeSlot(day, hour)) {}
    
    // copy constructor
    Section(const Section& rhs) 
    : name(rhs.name), vacant(rhs.vacant), slot(TimeSlot(rhs.getDay(), rhs.getHour())) {
        for (Student* currStudent : rhs.studentsFile) {
            Student* newStudent = new Student(* currStudent);           // creating a NEW student
            studentsFile.push_back(newStudent);                         // pushing back into copied student file
        }
    }

    void display(ostream& os) const {
        os << "Section: " << name << ", Time slot: [Day: " << slot.getDay() << ", Start time: ";
        os << slot.getFormattedHour() << "], Students: " << getStudents() << '\n';
    }

    string getSection() const {
        return name;
    }

    string getDay() const {
        return slot.getDay();
    }

    int getHour() const {
        return slot.getHour();
    }

    string getTimeSlot() const {
        return "[Day: " + slot.getDay() + ", Start time: " + slot.getFormattedHour() + "]";
    }

    string getStudents() const {
        if (studentsFile.size() == 0) {
            return "None";
        }
        string table = "\n";
        for (const Student *currStudent : studentsFile) {
            table = table + "Name: " + currStudent->getName() + ", Grades: \t"; // looks better...
            for (const int currGrade : currStudent->getGrades()) {
                table = table + to_string(currGrade) + ' ';
            }
            table = table + "\n";
        }
        return table;
    }

    bool getWorker() const {
        return vacant;
    }

    void setWorker(LabWorker& worker) {
        TA = &worker;
        vacant = false;
    }

    void addStudent(const string& name) {
        Student* newStudent = new Student(name);    // adding to the heap!
        studentsFile.push_back(newStudent);         // pushing back pointer
    }

    void addGrade(const string& student, int grade, int week) {
        for (Student* currStudent : studentsFile) {
            string currName = currStudent->getName();
            if (currName == student) {
                currStudent->addGrade(week, grade);
                return;
            }
        }
    }

    ~Section() {
        // destructor!
        cout << "\nSection " << name << " is being deleted\n";
        for (Student* currStudent : studentsFile) {
            cout << "Deleting " << currStudent->getName() << '\n';
            delete currStudent;
        }
    }

private:
        string name;
        TimeSlot slot;
        bool vacant;                    // TA vacancy 
        LabWorker* TA;                  // each TA can only have one section
        vector<Student*> studentsFile;  // can't create vector<Students>
};


class LabWorker {
public:
    LabWorker(const string& name) 
    : name(name), vacant(true), section(nullptr){}
    
    void display(ostream& os) const {
        if (section == nullptr) {
            os << name << " does not have a section\n";
        } else {
            os << name << " has Section: " << section->getSection() << ", Time Slot: ";
            os << section->getTimeSlot() << ", Students" << section->getStudents() << "\n";
        }
    }
    
    void addSection(Section& newSection) {
        if (vacant && newSection.getWorker()) {
            section = &newSection;
            vacant = false;
            newSection.setWorker(*this);
        } else if (!vacant){
            cout << name << " already has a section!\n";
        } else if (!newSection.getWorker()) {
            cout << newSection.getSection() << " already has a TA!\n";
        }
    }

    // moe.addGrade("Ringo", 7, 1);
    void addGrade(const string& student, int grade, int week) {
        section->addGrade(student, grade, week);
    }
private:
        string name;
        bool vacant;
        Section* section;
};

// define the prototypes
ostream& operator <<(ostream& os, const Section& mySection) {
    mySection.display(os);
    return os;
}

ostream& operator <<(ostream& os, const LabWorker& myWorker) {
    myWorker.display(os);
    return os;
}

// Test code
void doNothing(Section sec) { 
    // creates a copy (rhs) b/c we didn't pass by reference
    // NEEDS TO ALSO BE DELETED
    cout << sec;
}

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;
    // secA2.display(); <---- I didn't know how to overload the output operator before

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;
    // secA2.display();

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe("Moe");
    cout << moe << endl;
    // moe.display();

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection(secA2);
    // moe.display();
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection(secB3);
    cout << jane << endl;
    // jane.display();

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    // moe.display();
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    // moe.display();
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";
    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works properly, i.e. no memory leaks\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main