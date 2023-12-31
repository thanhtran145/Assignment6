#pragma once
#include "MyBagTemplate.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class Course
{
private:
    string name;
    MyBagTemplate<int> studentIDs;
    MyBagTemplate<string> studentNames;
    MyBagTemplate<double> studentScores;
    MyBagTemplate<char> studentGrades;

    char calculateGrade(double score) const
    {
        if (score >= 90.0) return 'A';
        else if (score >= 80.0) return 'B';
        else if (score >= 70.0) return 'C';
        else if (score >= 60.0) return 'D';
        else return 'F';
    }

public:

    //**************************** Constructor ************************//
    Course(const string& courseName) : name(courseName) {}

    //**************************** Accessor ***************************//
    const string& getName() const
    {
        return name;
    }

    int getNumStudents() const
    {
        return studentIDs.getSize();
    }

    const MyBagTemplate<int>& getStudentIDs() const
    {
        return studentIDs;
    }

    const MyBagTemplate<string>& getStudentNames() const
    {
        return studentNames;
    }

    //**************************** Mutator ***************************//
    void setName(const string newName)
    {
        name = newName;
    }

    //**************************** Member Functions ***********************//

    string getStudentName(int index) const
    {
        if (index >= 0 && index < studentIDs.getSize()) 
        {
            return studentNames[index];
        }
        else {
            return "Invalid Index";
        }
    }


    void addStudent(int ID, const string& name, double score) 
    {
        studentIDs.insert(ID);
        studentNames.insert(name);
        studentScores.insert(score);
        studentGrades.insert(calculateGrade(score));
    }

    bool removeStudent(int id) 
    {
        if (studentIDs.search(id))
        {
            int index = studentIDs.getSize() - 1;
            while (studentIDs[index] != id) {
                index--;
            }
            studentIDs[index] = studentIDs[studentIDs.getSize() - 1];
            studentNames[index] = studentNames[studentNames.getSize() - 1];
            studentScores[index] = studentScores[studentScores.getSize() - 1];
            studentGrades[index] = studentGrades[studentGrades.getSize() - 1];
            studentIDs.setSize(studentIDs.getSize() - 1);
            studentNames.setSize(studentNames.getSize() - 1);
            studentScores.setSize(studentScores.getSize() - 1);
            studentGrades.setSize(studentGrades.getSize() - 1);
            return true;
        }
        return false;
    }


    void displayCourse() const 
    {
        cout << "\n\t\t" << name;
        cout << "\n\t\tindex    StudentID                      Name    Score   Grade";
        for (int i = 0; i < studentIDs.getSize(); i++)
        {
            cout << "\n\t\t    " << i << "        " << studentIDs[i] << "                  " << studentNames[i] << "     " << right << setw(4) << studentScores[i] << "   " << studentGrades[i];
        }
        
        double average = 0;
        for (int i = 0; i < studentIDs.getSize(); i++)
        {
            average += studentScores[i];
        }

        if (studentIDs.getSize() == 1)
        {
            average = studentScores[0];
            cout << "\n\n\t\tAverage score and grade: " << average << "(" << calculateGrade(average) << ")\n";
        }
        else 
        {
            average /= studentGrades.getSize();

            cout << "\n\n\t\tAverage score and grade: " << average << "(" << calculateGrade(average) << ")\n";
        }
    }
};