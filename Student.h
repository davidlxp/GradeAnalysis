//
// Created by Xinpeng Liu on 2/14/22.
//

#ifndef GRADEANALYSIS_STUDENT_H
#define GRADEANALYSIS_STUDENT_H


#include <iostream>
#include <string>
#include <vector>

#include "AnswerSheet.h"
#include "UsefulTools.h"
using namespace std;

class Student {
public:
    Student(int stuId) { studentId = stuId; }
    Student(string, int);

    // ======================== Getters ======================== //

    /**
     * @Brief return a hashed unique ID for this Student object
     */
    size_t GetId();

    string GetStudent() { return studentName; }
    int GetStudentId() { return studentId; }

    /**
     * @Brief get a specific answer sheet from a student
     */
    AnswerSheet* GetAnswerSheetPtr(string, string, int);

    // ======================== Setters ======================== //

    /**
     * @Brief set student name
     */
    void SetStudent(string name) { studentName = name; }

    void SetStudentId(int id) { studentId = id; }

    /**
     * @Brief add AnswerSheet Pointer to the list
     */
    void AddAnswerSheetPtr(AnswerSheet*);

private:
    string studentName;
    int studentId;
    vector<AnswerSheet*> answerSheetPtrList;

    UsefulTools myTools;
};


#endif //GRADEANALYSIS_STUDENT_H
